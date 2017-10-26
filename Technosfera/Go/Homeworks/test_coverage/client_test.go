package main

import (
	"testing"
    "reflect"
    "net/http"
    "net/http/httptest"
    "time"
    "errors"
    "fmt"
    "net/url"
)

var (
	errTest = errors.New("testing")
	client  = &http.Client{Timeout: time.Second}
)

type TestCase struct {
	Req     SearchRequest
	Result  *SearchResponse
	IsError bool
}

func WrongFunc (w http.ResponseWriter, r *http.Request) {
    myLimit := r.URL.Query().Get("limit")
    if myLimit != "1"{
        w.WriteHeader(http.StatusInternalServerError)
    } else {
        w.Write([]byte("Normal'no"))
    }
}

func TestDummy(t *testing.T) {
    cases := []TestCase{
        TestCase {
            Req: SearchRequest{
                Limit: 20,
                Offset: 0,
                Query: "Boyd",
                OrderField: "",
                OrderBy: 1,
            },
            Result: &SearchResponse{
                Users: []User{{
                    Id: 0,
                    Name: "Boyd",
                    Gender: "male",
                    Age: 22,
                    About: "Nulla cillum enim voluptate consequat laborum esse excepteur occaecat commodo nostrud excepteur ut cupidatat. Occaecat minim incididunt ut proident ad sint nostrud ad laborum sint pariatur. Ut nulla commodo dolore officia. Consequat anim eiusmod amet commodo eiusmod deserunt culpa. Ea sit dolore nostrud cillum proident nisi mollit est Lorem pariatur. Lorem aute officia deserunt dolor nisi aliqua consequat nulla nostrud ipsum irure id deserunt dolore. Minim reprehenderit nulla exercitation labore ipsum.\n",
                },},
                NextPage: false,
            },
            IsError: false,
        },
        TestCase {
            Req: SearchRequest{
                Limit: 30,
                Offset: 0,
                Query: "th",
                OrderField: "",
                OrderBy: 0,
            },
            Result: &SearchResponse{
                Users: []User{{
                    Id: 22,
                    Name: "Beth",
                    Gender: "female",
                    Age: 31,
                    About: "Proident non nisi dolore id non. Aliquip ex anim cupidatat dolore amet veniam tempor non adipisicing. Aliqua adipisicing eu esse quis reprehenderit est irure cillum duis dolor ex. Laborum do aute commodo amet. Fugiat aute in excepteur ut aliqua sint fugiat do nostrud voluptate duis do deserunt. Elit esse ipsum duis ipsum.\n",
                },
                {
                    Id: 25,
                    Name: "Katheryn",
                    Gender: "female",
                    Age: 32,
                    About: "Magna excepteur anim amet id consequat tempor dolor sunt id enim ipsum ea est ex. In do ea sint qui in minim mollit anim est et minim dolore velit laborum. Officia commodo duis ut proident laboris fugiat commodo do ex duis consequat exercitation. Ad et excepteur ex ea exercitation id fugiat exercitation amet proident adipisicing laboris id deserunt. Commodo proident laborum elit ex aliqua labore culpa ullamco occaecat voluptate voluptate laboris deserunt magna.\n",
                },},
                NextPage: false,
            },
            IsError: false,
        },
        TestCase {
            Req: SearchRequest{
                Limit: 20,
                Offset: 0,
                Query: "th",
                OrderField: "",
                OrderBy: -1,
            },
            Result: &SearchResponse{
                Users: []User{{
                    Id: 25,
                    Name: "Katheryn",
                    Gender: "female",
                    Age: 32,
                    About: "Magna excepteur anim amet id consequat tempor dolor sunt id enim ipsum ea est ex. In do ea sint qui in minim mollit anim est et minim dolore velit laborum. Officia commodo duis ut proident laboris fugiat commodo do ex duis consequat exercitation. Ad et excepteur ex ea exercitation id fugiat exercitation amet proident adipisicing laboris id deserunt. Commodo proident laborum elit ex aliqua labore culpa ullamco occaecat voluptate voluptate laboris deserunt magna.\n",
                },
                {
                    Id: 22,
                    Name: "Beth",
                    Gender: "female",
                    Age: 31,
                    About: "Proident non nisi dolore id non. Aliquip ex anim cupidatat dolore amet veniam tempor non adipisicing. Aliqua adipisicing eu esse quis reprehenderit est irure cillum duis dolor ex. Laborum do aute commodo amet. Fugiat aute in excepteur ut aliqua sint fugiat do nostrud voluptate duis do deserunt. Elit esse ipsum duis ipsum.\n",
                },},
                NextPage: false,
            },
            IsError: false,
        },
        TestCase {
            Req: SearchRequest{
                Limit: 20,
                Offset: 0,
                Query: "th",
                OrderField: "Id",
                OrderBy: 1,
            },
            Result: &SearchResponse{
                Users: []User{{
                    Id: 22,
                    Name: "Beth",
                    Gender: "female",
                    Age: 31,
                    About: "Proident non nisi dolore id non. Aliquip ex anim cupidatat dolore amet veniam tempor non adipisicing. Aliqua adipisicing eu esse quis reprehenderit est irure cillum duis dolor ex. Laborum do aute commodo amet. Fugiat aute in excepteur ut aliqua sint fugiat do nostrud voluptate duis do deserunt. Elit esse ipsum duis ipsum.\n",
                },
                {
                    Id: 25,
                    Name: "Katheryn",
                    Gender: "female",
                    Age: 32,
                    About: "Magna excepteur anim amet id consequat tempor dolor sunt id enim ipsum ea est ex. In do ea sint qui in minim mollit anim est et minim dolore velit laborum. Officia commodo duis ut proident laboris fugiat commodo do ex duis consequat exercitation. Ad et excepteur ex ea exercitation id fugiat exercitation amet proident adipisicing laboris id deserunt. Commodo proident laborum elit ex aliqua labore culpa ullamco occaecat voluptate voluptate laboris deserunt magna.\n",
                },},
                NextPage: false,
            },
            IsError: false,
        },
        TestCase {
            Req: SearchRequest{
                Limit: 0,
                Offset: 0,
                Query: "th",
                OrderField: "Age",
                OrderBy: 1,
            },
            Result: &SearchResponse{
                Users: []User{},
                NextPage: true,
            },
            IsError: false,
        },
    }
            
    ts := httptest.NewServer(http.HandlerFunc(SearchServer))
    for caseNum, item := range cases {
		c := &SearchClient{
			AccessToken: CorrectAccessToken,
            URL: ts.URL,
		}
		result, err := c.FindUsers(item.Req)

		if err != nil && !item.IsError {
			t.Errorf("[%d] unexpected error: %#v", caseNum, err)
		}
		if err == nil && item.IsError {
			t.Errorf("[%d] expected error, got nil", caseNum)
		}
		if !reflect.DeepEqual(item.Result, result) {
			t.Errorf("[%d] wrong result, expected %#v, got %#v", caseNum, item.Result, result)
		}
	}
	ts.Close()
}

func TestErrors(t *testing.T) {
    cases := []TestCase{
        TestCase {
            Req: SearchRequest{
                Limit: -1,
                Offset: 0,
                Query: "Boyd",
                OrderField: "",
                OrderBy: 1,
            },
            Result: (*SearchResponse)(nil),
            IsError: true,
        },
        TestCase {
            Req: SearchRequest{
                Limit: 20,
                Offset: -1,
                Query: "Boyd",
                OrderField: "",
                OrderBy: 1,
            },
            Result: (*SearchResponse)(nil),
            IsError: true,
        },
        TestCase {
            Req: SearchRequest{
                Limit: 20,
                Offset: 0,
                Query: "Boyd",
                OrderField: "Gender",
                OrderBy: 1,
            },
            Result: (*SearchResponse)(nil),
            IsError: true,
        },
        TestCase {
            Req: SearchRequest{
                Limit: 20,
                Offset: 50,
                Query: "Boyd",
                OrderField: "",
                OrderBy: 1,
            },
            Result: (*SearchResponse)(nil),
            IsError: true,
        },
        TestCase {
            Req: SearchRequest{
                Limit: 20,
                Offset: 0,
                Query: "Boyd",
                OrderField: "",
                OrderBy: 55,
            },
            Result: (*SearchResponse)(nil),
            IsError: true,
        },
    }
     ts := httptest.NewServer(http.HandlerFunc(SearchServer))
    for caseNum, item := range cases {
		c := &SearchClient{
			AccessToken: CorrectAccessToken,
            URL: ts.URL,
		}
		result, err := c.FindUsers(item.Req)

		if err != nil && !item.IsError {
			t.Errorf("[%d] unexpected error: %#v", caseNum, err)
		}
		if err == nil && item.IsError {
			t.Errorf("[%d] expected error, got nil", caseNum)
		}
		if !reflect.DeepEqual(item.Result, result) {
			t.Errorf("[%d] wrong result, expected %#v, got %#v", caseNum, item.Result, result)
		}
	}
    ts.Close()
}

func TestOther (t *testing.T) {
    case1 := TestCase {
        Req: SearchRequest{
            Limit: 20,
            Offset: 0,
            Query: "Boyd",
            OrderField: "",
            OrderBy: 1,
        },
        Result: &SearchResponse{
            Users: []User{{
                Id: 0,
                Name: "Boyd",
                Gender: "male",
                Age: 22,
                About: "Nulla cillum enim voluptate consequat laborum esse excepteur occaecat commodo nostrud excepteur ut cupidatat. Occaecat minim incididunt ut proident ad sint nostrud ad laborum sint pariatur. Ut nulla commodo dolore officia. Consequat anim eiusmod amet commodo eiusmod deserunt culpa. Ea sit dolore nostrud cillum proident nisi mollit est Lorem pariatur. Lorem aute officia deserunt dolor nisi aliqua consequat nulla nostrud ipsum irure id deserunt dolore. Minim reprehenderit nulla exercitation labore ipsum.\n",
            },},
            NextPage: false,
        },
        IsError: true,
    }
    case2 := TestCase {
        Req: SearchRequest{
            Limit: 30,
            Offset: 0,
            Query: "",
            OrderField: "",
            OrderBy: 1,
        },
        Result: &SearchResponse{
            Users: []User{},
            NextPage: false,
        },
        IsError: false,
    }
    case3 := TestCase {
        Req: SearchRequest{
            Limit: 0,
            Offset: 0,
            Query: "",
            OrderField: "",
            OrderBy: 1,
        },
        Result: &SearchResponse{
            Users: []User{},
            NextPage: false,
        },
        IsError: false,
    }
    
    ts := httptest.NewServer(http.HandlerFunc(SearchServer))
    c1 := &SearchClient{
        AccessToken: "d41d8cd98f00b204e9800998ecf8417e", //incorrect token
        URL: ts.URL,
    }
    _, err := c1.FindUsers(case1.Req)
    if err == nil {
        t.Errorf("Expected error: %#v", err)
    }
    client = &http.Client{Timeout: time.Nanosecond}
    
    c := &SearchClient{
        AccessToken: CorrectAccessToken,
        URL: ts.URL,
    }
    _, err = c.FindUsers(case1.Req)
    if err == nil {
        t.Errorf("Expected error: %#v", err)
    }
    client = &http.Client{Timeout: time.Second, Transport: &http.Transport{Proxy: func(*http.Request) (*url.URL, error){return nil, fmt.Errorf("err")}}}
    result, err := c.FindUsers(case1.Req)
    if err == nil{
        t.Errorf("Expected errr")
    }
    client = &http.Client{Timeout: time.Second}
    result, err = c.FindUsers(case2.Req)
    if err != nil {
        t.Errorf("Unexpected error: %#v", err)
    }
    if len(result.Users) != 25 {
        t.Errorf("Wrong result, expected %d, got %d", 25, len(result.Users))
    }
    ts.Close()
    ts1 := httptest.NewServer(http.HandlerFunc(WrongFunc))
    c2 := &SearchClient{
        AccessToken: CorrectAccessToken,
        URL: ts1.URL,
    }
    result, err = c2.FindUsers(case2.Req)
    if err == nil {
        t.Errorf("Expected error")
    }
    result, err = c2.FindUsers(case3.Req)
    if err == nil {
        t.Errorf("Expected error")
    }
    ts1.Close()
}
