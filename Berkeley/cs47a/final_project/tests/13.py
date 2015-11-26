test = {
  'name': 'Question 13',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          scm> (define (f) False)
          5e9740437eba0d6fc4d5ab5f9dd3d30b
          # locked
          scm> (if (f) 1 0)
          9815d8391210230341d3c0942b067539
          # locked
          scm> (if f 1 0)
          7107157269a542fea41c45a208299f75
          # locked
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          scm> (if True 1 0)
          7107157269a542fea41c45a208299f75
          # locked
          scm> (if False 1 0)
          9815d8391210230341d3c0942b067539
          # locked
          scm> (if 1 1 0)
          7107157269a542fea41c45a208299f75
          # locked
          scm> (if 0 1 0)
          7107157269a542fea41c45a208299f75
          # locked
          scm> (if 'a 1 0)
          7107157269a542fea41c45a208299f75
          # locked
          scm> (if (cons 1 2) 1 0)
          7107157269a542fea41c45a208299f75
          # locked
          scm> (if True 1)
          7107157269a542fea41c45a208299f75
          # locked
          scm> (if False 1)
          567dc50b5f172929c23f03f6621d0d6b
          # locked
          scm> (eval (if False 1))
          567dc50b5f172929c23f03f6621d0d6b
          # locked
          scm> (if True '(1))
          9f90814c29b45aacdbe10436cf085857
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
    }
  ]
}