(define (atom? x) (not (pair? x)))


(define (deep-map fn s)
  (cond
   ((null? s) '())
   ((atom? (car s)) 
      (cons (fn (car s)) (deep-map fn (cdr s))))
   (else 
      (cons (deep-map fn (car s)) (deep-map fn (cdr s))))
  )
)

(define (substitute s old new)
  (deep-map 
       (lambda (wrd) 
         (if (eq? wrd old) new wrd))
       s
  )
)

(define (sub-all s olds news)
  (cond 
    ((null? olds) s)
    (else (sub-all 
	    (substitute s (car olds) (car news))
	    (cdr olds)
	    (cdr news)))
  )
)


