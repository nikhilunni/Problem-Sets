test = {
  'name': 'Question 4',
  'points': 2,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> env = create_global_frame()
          >>> twos = Pair(2, Pair(2, nil))
          >>> plus = PrimitiveProcedure(scheme_add) # + procedure
          >>> scheme_apply(plus, twos, env)
          20bc71417eab0e038125723df967189e
          # locked
          # choice: 4
          # choice: SchemeError
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          >>> env = create_global_frame()
          >>> twos = Pair(2, Pair(2, nil))
          >>> oddp = PrimitiveProcedure(scheme_oddp) # odd? procedure
          >>> scheme_apply(oddp, twos, env)
          afe8b0293088a787c654885143501f84
          # locked
          # choice: True
          # choice: False
          # choice: SchemeError
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          >>> env = create_global_frame()
          >>> two = Pair(2, nil)
          >>> eval = PrimitiveProcedure(scheme_eval, True) # eval procedure
          >>> scheme_apply(eval, two, env) # be sure to check use_env
          2
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> env = create_global_frame()
          >>> args = nil
          >>> def make_scheme_counter():
          ...     x = 0
          ...     def scheme_counter():
          ...         nonlocal x
          ...         x += 1
          ...         return x
          ...     return scheme_counter
          >>> counter = PrimitiveProcedure(make_scheme_counter()) # counter
          >>> scheme_apply(counter, args, env) # only call procedure.fn once!
          1
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': r"""
      >>> from scheme import *
      """,
      'teardown': '',
      'type': 'doctest'
    },
    {
      'cases': [
        {
          'code': r"""
          scm> (+ 2 3)
          5
          scm> (+)
          0
          scm> (* (+ 3 2) (+ 1 7))
          40
          scm> (odd? 13)
          True
          scm> (car (list 1 2 3 4))
          1
          scm> (car car)
          SchemeError
          scm> (odd? 1 2 3)
          SchemeError
          scm> (1 2)
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