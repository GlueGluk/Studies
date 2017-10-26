package main

import (
	"net/http"
    "encoding/xml"
    "io/ioutil"
    "sort"
    "strings"
    "strconv"
    "encoding/json"
    _"fmt"
)

type UserSet struct {
    Version     string   `xml:"version,attr"`
    Encoding    string   `xml:"encoding,attr"`
    List        []User   `xml:"row"`
}

const (
	CorrectAccessToken = "d41d8cd98f00b204e9800998ecf8427e"
)

type By func(p1, p2 *User) bool

func (by By) Sort(users []User) {
	us := &userSorter{
		users: users,
		by:    by, // The Sort method's receiver is the function (closure) that defines the sort order.
	}
	sort.Sort(us)
}

type userSorter struct {
	users []User
	by    func(p1, p2 *User) bool // Closure used in the Less method.
}

// Len is part of sort.Interface.
func (s *userSorter) Len() int {
	return len(s.users)
}

// Swap is part of sort.Interface.
func (s *userSorter) Swap(i, j int) {
	s.users[i], s.users[j] = s.users[j], s.users[i]
}

// Less is part of sort.Interface. It is implemented by calling the "by" closure in the sorter.
func (s *userSorter) Less(i, j int) bool {
	return s.by(&s.users[i], &s.users[j])
}


func SearchServer(w http.ResponseWriter, r *http.Request) {
    token := r.Header.Get("AccessToken")
    if token != CorrectAccessToken {
        w.WriteHeader(http.StatusUnauthorized)
        return
    }
    bs, err := ioutil.ReadFile("dataset.xml")
    if err != nil {
        w.WriteHeader(http.StatusInternalServerError)
        return
    }
	base := new(UserSet)
	err = xml.Unmarshal(bs, &base)
    if err != nil {
        w.WriteHeader(http.StatusInternalServerError)
        return
	}
    
    name := func(u1, u2 *User) bool {
		return u1.Name < u2.Name
	}
	id := func(u1, u2 *User) bool {
		return u1.Id < u2.Id
	}
	age := func(u1, u2 *User) bool {
		return u1.Age < u2.Age
	}
    var sortFunc By
    var retData []User
    
    myQuery := r.URL.Query().Get("query")
    if myQuery == "" {
        retData = base.List
    } else {
        for _, u := range base.List {
            if (strings.Contains(u.Name, myQuery) || strings.Contains(u.About, myQuery)) {
                retData = append(retData, u)
            }
        }
    }
    myOrder := r.URL.Query().Get("order_field")
    if myOrder == "Id" {
        sortFunc = id
    } else if myOrder == "Age" {
        sortFunc = age
    } else if (myOrder == "Name") || (myOrder == ""){
        sortFunc = name
    } else {
        w.WriteHeader(http.StatusBadRequest)
        errResp := SearchErrorResponse{ Error: ErrorBadOrderField}
        res, err := json.Marshal(errResp)
        if err!= nil {
            w.WriteHeader(http.StatusInternalServerError)
        }
        w.Write(res)
        return
    }
    myOrderBy := r.URL.Query().Get("order_by")
    if myOrderBy == "1" {
        By(sortFunc).Sort(retData)
    } else if myOrderBy == "-1" {
        sort.Sort(sort.Reverse(&userSorter{users: retData, by: sortFunc}))
    } else if myOrderBy != "0" {
        w.WriteHeader(http.StatusBadRequest)
        res, err := json.Marshal("Bad order_by")
        if err!= nil {
            w.WriteHeader(http.StatusInternalServerError)
        }
        w.Write(res)
    }
    myOffset, _ := strconv.Atoi(r.URL.Query().Get("offset"))
    if myOffset >= len(retData) {
        w.WriteHeader(http.StatusBadRequest)
        errResp := SearchErrorResponse{Error: "Too big offset"}
        res, err := json.Marshal(errResp)
        if err!= nil {
            w.WriteHeader(http.StatusInternalServerError)
        }
        w.Write(res)
        return
    } else {
        retData = retData[myOffset:]
    }
    myLimit, _ := strconv.Atoi(r.URL.Query().Get("limit"))
    if myLimit < len(retData) {
        retData = retData[:myLimit]
    }    
    res, err := json.Marshal(retData)
    if err!= nil {
        w.WriteHeader(http.StatusInternalServerError)
        return
    }
    w.Write(res)
}
