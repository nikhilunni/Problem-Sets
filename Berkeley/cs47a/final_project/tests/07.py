test = {
  'name': 'Question 7',
  'points': 2,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> eval_all(Pair(2, nil), env)
          9ea224e62b219a1ee61849f282da5e65
          # locked
          >>> eval_all(Pair(4, Pair(5, nil)), env)
          020ab0752ad7f917c8c0e4ac6c80edf7
          # locked
          >>> eval_all(nil, env) # return okay (meaning undefined)
          567dc50b5f172929c23f03f6621d0d6b
          # locked
          """,
          'hidden': False,
          'locked': True
        }
      ],
      'scored': True,
      'setup': r"""
      >>> from scheme import *
      >>> env = create_global_frame()
      """,
      'teardown': '',
      'type': 'doctest'
    },
    {
      'cases': [
        {
          'code': r"""
          scm> (begin (+ 2 3) (+ 5 6))
          f54db2615aab72a9f68c6adc5412f9c0
          # locked
          scm> (begin (define x 3) x)
          5d8831cb01cb0c9d130940fa232fd534
          # locked
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          scm> (begin 30 '(+ 2 2))
          0d798a693faed471124ad0f20a07036f
          # locked
          # choice: (+ 2 2)
          # choice: '(+ 2 2)
          # choice: 4
          # choice: 30
          scm> (define x 0)
          57775d5ff999af0ee4cbfa3aa0507be8
          # locked
          scm> (begin 42 (define x (+ x 1)))
          57775d5ff999af0ee4cbfa3aa0507be8
          # locked
          scm> x
          7107157269a542fea41c45a208299f75
          # locked
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          scm> (begin 30 'hello)
          hello
          scm> (begin (define x 3) (cons x '(y z)))
          (3 y z)
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