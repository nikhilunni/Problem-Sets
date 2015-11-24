(define (cddr s)
  (cdr (cdr s)))

(define (cadr s)
  (car (cdr s))
)

(define (caddr s)
  (car (cddr s))
)

(define (sign x)
  (cond
     ((> x 0) 1)
     ((= x 0) 0)
     ((< x 0) -1))
)

(define (square x) (* x x))

(define (pow b n)
  (cond
     ((= n 1) b)
     ((even? n) (pow (* b b) (/ n 2)))
     ((odd? n) (* b (pow (* b b) (/ (- n 1) 2)))))
)

(define (ordered? s)
  (if (null? (cdr s))
      'True
      (and ( >= (cadr s) (car s)) (ordered? (cdr s))))
)

(define (atom? x) (not (pair? x)))

(define (nodots s)
    (cond
        ((null? s) '())
        ((atom? s) (list s))
	((atom? (car s)) (cons (car s) (nodots (cdr s))))
	(else (cons 
	          (nodots (car s))
		  (nodots (cdr s))
	      )
	)
    )
)

; Sets as sorted lists

(define (empty? s) (null? s))

(define (contains? s v)
    (cond ((empty? s) false)
	  ((> (car s) v) false)
	  ((= (car s) v) true)
          (else (contains? (cdr s) v))
          ))

; Equivalent Python code, for your reference:
;
; def empty(s):
;     return len(s) == 0
;
; def contains(s, v):
;     if empty(s):
;         return False
;     elif s.first > v:
;         return False
;     elif s.first == v:
;         return True
;     else:
;         return contains(s.rest, v)

(define (add s v)
    (cond ((empty? s) (list v))
	  ((< v (car s)) (cons v s))
	  ((= v (car s)) s)
          (else (cons (car s) (add (cdr s) v)))
          ))

(define (intersect s t)
    (cond ((empty? s) nil)
	  ((contains? t (car s)) (cons (car s) (intersect (cdr s) t)))
	  (else (intersect (cdr s) t))
	  ))

; Equivalent Python code, for your reference:
;
; def intersect(set1, set2):
;     if empty(set1) or empty(set2):
;         return Link.empty
;     else:
;         e1, e2 = set1.first, set2.first
;         if e1 == e2:
;             return Link(e1, intersect(set1.rest, set2.rest))
;         elif e1 < e2:
;             return intersect(set1.rest, set2)
;         elif e2 < e1:
;             return intersect(set1, set2.rest)

(define (union s t)
    (cond ((empty? s) t)
	  ((empty? t) s)
	  ((< (car s) (car t)) (cons (car s) (union (cdr s) t)))
	  ((> (car s) (car t)) (cons (car t) (union s (cdr t))))
	  ((= (car s) (car t)) (cons (car t) (union (cdr s) (cdr t))))
          ))


; Binary search trees

; A data abstraction for binary trees where nil represents the empty tree
(define (tree entry left right) (list entry left right))
(define (entry t) (car t))
(define (left t) (cadr t))
(define (right t) (caddr t))
(define (empty? s) (null? s))
(define (leaf entry) (tree entry nil nil))

(define (in? t v)
    (cond ((empty? t) false)
	  ((= v (entry t)) true)
          (else (or (in? (left t) v) (in? (right t) v)))
          ))

; Equivalent Python code, for your reference:
;
; def contains(s, v):
;     if s.is_empty:
;         return False
;     elif s.entry == v:
;         return True
;     elif s.entry < v:
;         return contains(s.right, v)
;     elif s.entry > v:
;         return contains(s.left, v)

(define (concat s t)
    (cond 
        ((null? s) t)
        ((null? t) s)
	((null? (cdr s)) (cons (car s) t))
	(else (cons (car s) (concat (cdr s) t)))
	))

(define (as-list t)
    (cond 
        ((empty? t) '())
        (else (concat 
	          (as-list (left t)) 
                  (cons (entry t) (as-list (right t)))))
        ))

