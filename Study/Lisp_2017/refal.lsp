;Машигина Наталья Владимировна, 325 группа
;Вариант "Отождествление рефал-выражений"
;Для запуска функции Match1 на вход нужно подать 2 лисповских списка: первый список - шаблон, второй - отождествляемое выражение.
;В шаблоне все переменные нужно указывать в кавычках (например "e1").
;Тесты находятся в конце файла.


(defun put (a name p) (setf (get a name) p))

(defun Match1 (l1 l2) (put 'ITEMS 'LIST nil)  ;вывод результата
	(cond ((Match l1 l2) (print "Got: ")(cout (get 'ITEMS 'LIST)) T)
		  (T nil)))
		  
(defun cout (l1)
	(cond ((null l1) nil)
		  ((eql (car l1) '\|) (cout(cdr l1)))
		  ((and (no_more (car l1) (cdr l1)) (or(or(or (eql (char (string (car l1)) 0) '#\e) (eql (char (string (car l1)) 0) '#\v)) (eql (char (string (car l1)) 0) '#\s))
														(eql (char (string (car l1)) 0) '#\w))) (princ (string (car l1))) (princ "=>") (princ (get (car l1) 'MNG)) (princ ";  ") (cout (cdr l1)))
		  (T (cout (cdr l1)))))

(defun Match (li1 li2) ;(print "In Match: ") (print li1) (print li2);сопоставление
    (cond ((and (null li1) (null li2)) T) 
		  ((null li1) (ret (get 'ITEMS 'LIST) li1 li2))
		  ((atom (car li1)) ;(print (char (string (car li1)) 0))
			  (cond ((eql (char (string (car li1)) 0) '#\e) (e li1 li2))
					((string-equal (char (string (car li1)) 0) '#\v) (v li1 li2))
					((string-equal (char (string (car li1)) 0) '#\s) (s li1 li2))
					((string-equal (char (string (car li1)) 0) '#\w) (w li1 li2))
					(T (expr li1 li2))))
		  ((atom (car li2)) (ret (get 'ITEMS 'LIST) li1 li2))
		  (T (put 'ITEMS 'LIST (cons '\| (get 'ITEMS 'LIST)))(cond ((and (Match (car li1) (car li2)) (Match (cdr li1) (cdr li2))) T) 
																  (T (ret (get 'ITEMS 'LIST) li1 li2))))))	  

(defun expr (l1 l2) ;(print "In expr") (print l1) (print l2) 
	(cond ((eql (car l1) (car l2)) (put 'ITEMS 'LIST (cons (car l1) (get 'ITEMS 'LIST))) (Match (cdr l1) (cdr l2)))
		  (T (ret (get 'ITEMS 'LIST) l1 l2))))
		  
(defun e (ll1 ll2) ;(print "in e") (print ll1) (print ll2)
	(cond ((eq (get 'ITEMS 'LIST) nil) (put 'ITEMS 'LIST (list (intern (car ll1)))) (put (intern (car ll1)) 'MNG nil) (put (intern (car ll1)) 'TAIL ll2) ;(print "Tail put:") (print (get (intern (car ll1)) 'TAIL)) 
																															(Match (cdr ll1) ll2))
		  ((eq (srch (car ll1) (get 'ITEMS 'LIST)) nil) (put 'ITEMS 'LIST (cons (intern (car ll1)) (get 'ITEMS 'LIST))) (put (intern (car ll1)) 'MNG nil) (put (intern (car ll1)) 'TAIL ll2) (Match (cdr ll1) ll2))
		  (T (cut (get (intern (car ll1)) 'MNG) ll1 ll2))))
		  
(defun v (l1 l2) ;(print "in v")
	(cond ((null l2) (ret (get 'ITEMS 'LIST) l1 l2))
		  ((eq (get 'ITEMS 'LIST) nil) (put 'ITEMS 'LIST (list (intern (car l1)))) (put (intern (car l1)) 'MNG (list(car l2))) (put (intern (car l1)) 'TAIL (cdr l2)) (Match (cdr l1) (cdr l2)))
		  ((eq (srch (car l1) (get 'ITEMS 'LIST))  nil) (put 'ITEMS 'LIST (cons (intern (car l1)) (get 'ITEMS 'LIST))) (put (intern (car l1)) 'MNG (list (car l2))) (put (intern (car l1)) 'TAIL (cdr l2)) (Match (cdr l1) (cdr l2)))
		  (T (cut (get (intern (car l1)) 'MNG) l1 l2))))
		  
(defun s (l1 l2) ;(print "in s")
	(cond ((or (null l2) (null (car l2))) (ret (get 'ITEMS 'LIST) l1 l2)) 
		  ((not (atom (car l2))) (ret (get 'ITEMS 'LIST) l1 l2))
		  ((eq (get 'ITEMS 'LIST) nil) (put 'ITEMS 'LIST (list (intern (car l1)))) (put (intern (car l1)) 'MNG (car l2)) (Match (cdr l1) (cdr l2)) )
		  ((eq (srch (car l1) (get 'ITEMS 'LIST) )  nil) (put 'ITEMS 'LIST (cons (intern (car l1)) (get 'ITEMS 'LIST))) (put (intern (car l1)) 'MNG (car l2)) (Match (cdr l1) (cdr l2)))
		  (T (cut (get (intern (car l1)) 'MNG) l1 l2))))
		  
(defun w (l1 l2) ;(print "in w")
	(cond ((null(car l2)) (ret (get 'ITEMS 'LIST) l1 l2))
		  ((eq (get 'ITEMS 'LIST) nil) (put 'ITEMS 'LIST (list (intern (car l1)))) (put (intern (car l1)) 'MNG (car l2)) (Match (cdr l1) (cdr l2)) )
		  ((eq (srch (car l1) (get 'ITEMS 'LIST)) nil) (put 'ITEMS 'LIST (cons (intern (car l1)) (get 'ITEMS 'LIST))) (put (intern (car l1)) 'MNG (car l2)) (Match (cdr l1) (cdr l2)))
		  (T (cut (get (intern (car l1)) 'MNG) l1 l2))))
		  
(defun reduceR (f l a) ;функционал свертки
	(cond ((null l) a)
		  (T (funcall f (car l) (reduceR f (cdr l) a)))))
		  
(defun srch (str1 l1) (reduceR #'(lambda (x y) (or x y)) (mapcar #'(lambda (z) (string-equal (string str1) (string z))) l1) nil))

(defun cut (l1 l2 l3)
	(cond ((null l1) (put 'ITEMS 'LIST (cons (intern (car l2)) (get 'ITEMS 'LIST))) (Match (cdr l2) l3) )
		  ((atom l1) (cond ((and (atom (car l3)) (eq (car l3) l1))  (put 'ITEMS 'LIST (cons (intern (car l2)) (get 'ITEMS 'LIST))) (Match (cdr l2) (cdr l3)))
						   (T (ret (get 'ITEMS 'LIST) l2 l3))))
		  ((pred_cut l1 l3) (put 'ITEMS 'LIST (cons (intern (car l2)) (get 'ITEMS 'LIST))) (Match (cdr l2) (do_cut l1 l3)))
		  (T (ret (get 'ITEMS 'LIST) l2 l3))))

(defun pred_cut (l1 l2)
	(cond ((null l1) T)
		  ((atom l1) (cond ((atom l2) (eq l1 l2))
						   ((atom (car l2)) (eq (car l2) l1))
						   (T nil)))
		  ((atom l2) nil)
		  ((pred_cut (car l1) (car l2)) (pred_cut (cdr l1) (cdr l2)))))

(defun do_cut (l1 l2)
	(cond ((null l1) l2)
		  ((atom l1) (cond ((and (atom l2) (eq l1 l2)) ())
						   ((and (atom (car l2)) (eq (car l2) l1)) (cdr l2))
						   (T nil)))
		  ((atom l2) nil)
		  (T (do_cut (cdr l1) (cdr l2)))))
		  
(defun ret (l1 l2 l3); возврат при неправильном сопоставлении
	(cond ((null l1) nil)
		  ((eq (car l1) '\|) (put 'ITEMS 'LIST (cdr l1)) nil)
		  ((and (and (or (eql (char (string (car l1)) 0) '#\e) (eql (char (string (car l1)) 0) '#\v)) (no_more (car l1) (cdr l1))) (not (null (get (car l1) 'TAIL)))) ;(print "REPLACING________")
				(put (car l1) 'MNG (append (get (car l1) 'MNG) (list (car (get (car l1) 'TAIL)) ))) (put (car l1) 'TAIL (cdr(get (car l1) 'TAIL))) (Match l2 (get (car l1) 'TAIL)))
		  (T (put 'ITEMS 'LIST (cdr l1)) (cond ((or(or(or (eql (char (string (car l1)) 0) '#\e) (eql (char (string (car l1)) 0) '#\v)) (eql (char (string (car l1)) 0) '#\s))
														(eql (char (string (car l1)) 0) '#\w)) (ret (cdr l1) (cons (string (car l1)) l2) l3))
											   (T (ret (cdr l1) (cons (car l1) l2) l3))))))
		  
(defun no_more (s1 l1) ;(print "in no_more")
	(reduceR #'(lambda (x y) (and x y)) (mapcar #'(lambda (z) (not (string-equal (string s1) (string z)))) l1) T))

(print "Example: (e1 sa e2 sa) (abc a b b), expected T")		  
(print (Match1 '("e1" "sa" "e2" "sa") '(abc a b b)))  
(print "Example: (e1 sa e2 sa sb) (abc a b b), expected nil")
(print (Match1 '("e1" "sa" "e2" "sa" "sb") '(abc a b b)))   
(print "Example: (v1 (sa c+1) sa e2) (abc (a b) (c c+1) c a), expected T")
(print (Match1 '("v1" ("sa" c+1) "sa" "e2") '(abc (a b) (c c+1) c a)))   
(print "Example: (e1 (sa c+1) sa e2) (abc (a b) (c c+1) a), expected nil")
(print (Match1 '("e1" ("sa" c+1) "sa" "e2") '(abc (a b) (c c+1) a))) 
(print "Example: (e1 (sa e2) sa sb) (abc (b a) b a), expected T")
(print (Match1 '("e1" ("sa" "e2") "sa" "sb") '(abc (b a) b a)))  
(print "Example: (e1 (sa e2) sa sb) (abc (b a) c a), expected nil")
(print (Match1 '("e1" ("sa" "e2") "sa" "sb") '(abc (b a) c a)))  
(print "Example: (e1 (e1 sa) (sa (sa e2)) e2) (a (a b) (b (c))), expected nil")
(print (Match1 '("e1" ("e1" "sa") ("sa" ("sa" "e2")) "e2") '(a (a b) (b (c))) )) 
(print "Example: (e1 (e3 sa) (sa (sa e2)) e2) (a (a b) (c) (c (c k (ab))) k (ab) ), expected T") 
(print (Match1 '("e1" ("e3" "sa") ("sa" ("sa" "e2")) "e2") '(a (a b) (c) (c (c k (ab))) k (ab)) ))  
(print "Example:  (e1 (e2) (e3((e4 e5) e6) v7) v8 (v9) eA)  (f (a b) (c ((d e) g) h) i (h)), expected T") 
(print (Match1 '("e1" ("e2") ("e3"(("e4" "e5") "e6") "v7") "v8" ("v9") "eA") '(f (a b) (c ((d e) g) h) i (h))))   
(print "Example:  (e1 (e2) (e3((e4 e5) e6) v7) v8 (v9) vA)  (f (a b) (c ((d e) g) h) i (h)), expected nil") 
(print (Match1 '("e1" ("e2") ("e3"(("e4" "e5") "e6") "v7") "v8" ("v9") "vA") '(f (a b) (c ((d e) g) h) i (h)))) 
(print "Example:  (sa)  ((d)), expected nil") 
(print (Match1 '("sA") '((d)))) 
(print "Example:  (wa)  ((d)), expected T") 
(print (Match1 '("wA") '((d)))) 
(print "Example: () (a), expected nil") 
(print (Match1 '() '(a))) 
(print "Example: (e1 a s2 e3 s2 s4) (a s d a d s a a s d), expected T" )
(print (Match1 '("e1" a "s2" "e3" "s2" "s4") '(a s d a d s a a s d) ))