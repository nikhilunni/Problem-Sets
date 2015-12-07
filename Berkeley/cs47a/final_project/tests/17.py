test = {
  'name': 'Question 17',
  'points': 2,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          scm> (define f (mu (x) (+ x y)))
          5e9740437eba0d6fc4d5ab5f9dd3d30b
          # locked
          scm> (define g (lambda (x y) (f (+ x x))))
          279b14735aeede45f020ca967b462dca
          # locked
          scm> (g 3 7)
          a6be3206207ecfbca3f41ef566207251
          # locked
          """,
          'hidden': False,
          'locked': True
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'scheme'
    },
    {
      'cases': [
        {
          'code': r"""
          scm> (define h (mu () x))
          h
          scm> (define (high fn x) (fn))
          high
          scm> (high h 2)
          2
          scm> (define (f x) (mu () (lambda (y) (+ x y))))
          f
          scm> (define (g x) (((f (+ x 1))) (+ x 2)))
          g
          scm> (g 3)
          8
          scm> (mu ())
          SchemeError
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'scheme'
    }
  ]
}