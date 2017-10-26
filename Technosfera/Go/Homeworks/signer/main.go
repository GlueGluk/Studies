package main

import (
	_"fmt"
	"strconv"
	"sync"
	"sort"
)

func ExecutePipeline(funcs ...job){
	in := make(chan interface{})
	wg := &sync.WaitGroup{}
	for _, f := range funcs {
		wg.Add(1)
		fun := f
		out := make (chan interface {})
		go func (in, out chan interface{}){
			defer wg.Done()
			fun(in, out)
			close(out)
		}(in, out)
		in = out
	}
	wg.Wait()
}

func SingleHash (in, out chan interface{}){
//	fmt.Println("Singlehash")
	var dataGot []string
	for data := range in {
		tmp := strconv.Itoa(data.(int))
		dataGot = append(dataGot, tmp)
	}
	wg := &sync.WaitGroup{}
	for _, s := range dataGot {
		mdRes := DataSignerMd5(s)
		wg.Add(1)
		go func (out chan interface{}, s, mdRes string) {
			defer wg.Done()
			var chans [2](chan string)
			for j := 0; j<2 ; j++ {
				chans[j] = make (chan string)
			}
			go func (out chan string, s string) {
				out <- DataSignerCrc32(s)
				close(out)
			}(chans[0], s) 
			go func (out chan string, s string) {
				out <- DataSignerCrc32(s)
				close(out)
			}(chans[1], mdRes)
			s0 := <-chans[0] 
			s1 := <-chans[1] 
			str := s0+"~"+s1
			out <- str 
		}(out, s, mdRes)
	}
	wg.Wait()
//	fmt.Println("Single ends")
}

func MultiHash (in, out chan interface{}) {
//	fmt.Println("Multihash")
	wg := &sync.WaitGroup{}
	for data := range in {
		wg.Add(1)
		go func (out chan interface{}, data interface{}) {
			defer wg.Done()
			var chans [6](chan string)
			for j := 0; j<6 ; j++ {
				chans[j] = make (chan string)
			}
			for i := 0; i < 6; i++ {
				go func(th int, out chan<- string) {
					out <- DataSignerCrc32(strconv.Itoa(th)+data.(string))
					close(out)
				}(i, chans[i])
			}
			res := <-chans[0]
			str := res
			for i := 1; i < 6; i++ {
				res = <-chans[i]
				str += res
			}
			out <- str
		}(out, data)
	}
	wg.Wait()
//	fmt.Println("Multi ends")
}

func CombineResults (in, out chan interface{}) {
//	fmt.Println("CombineResults")
	var strs []string
	for s := range in{
		strs = append (strs, s.(string))
	}
	sort.Strings(strs)
	str := ""
	for _, st := range strs {
		if(str != "") {
			str += "_"
		}
		str += st
	}
	out <- str
}
