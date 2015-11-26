test = {
  'name': 'Question 14',
  'partner': 1,
  'points': 2,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          scm> (and)
          64c3594f9a1ee2dfe655adc89a92fdf0
          # locked
          # choice: True
          # choice: False
          # choice: SchemeError
          scm> (and 1 False)
          e681e19fc3ebbe87634352890af17d2d
          # locked
          # choice: 1
          # choice: True
          # choice: False
          scm> (and (+ 1 1) 1)
          7107157269a542fea41c45a208299f75
          # locked
          # choice: 2
          # choice: 1
          # choice: (+ 1 1)
          # choice: True
          scm> (and False 5)
          e681e19fc3ebbe87634352890af17d2d
          # locked
          # choice: 5
          # choice: True
          # choice: False
          scm> (and 4 5 (+ 3 3))
          d6419fcc8408979e711f47a3e32f8a1f
          # locked
          scm> (and True False 42 (/ 1 0))
          e681e19fc3ebbe87634352890af17d2d
          # locked
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          scm> (define x 0)
          x
          scm> (and 3 (define x (+ x 1)))
          x
          scm> x
          1
          scm> (and (begin (define x (+ x 1)) False) 3)
          False
          scm> (and False (begin (define x (+ x 1)) 3))
          False
          scm> x
          2
          scm> (and 3 2 False)
          False
          scm> (and 3 2 1)
          1
          scm> (and 3 False 5)
          False
          """,
          'hidden': False,
          'locked': False
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
          scm> (or)
          e681e19fc3ebbe87634352890af17d2d
          # locked
          # choice: True
          # choice: False
          # choice: SchemeError
          scm> (or (+ 1 1))
          9ea224e62b219a1ee61849f282da5e65
          # locked
          # choice: 2
          # choice: True
          # choice: False
          # choice: (+ 1 1)
          scm> (or False)
          e681e19fc3ebbe87634352890af17d2d
          # locked
          # choice: True
          # choice: False
          # choice: SchemeError
          scm> (define (t) True)
          e9b8fd6a748b4351172f194ebe8ccb25
          # locked
          scm> (or (t) 3)
          64c3594f9a1ee2dfe655adc89a92fdf0
          # locked
          # choice: 3
          # choice: True
          # choice: False
          scm> (or 5 2 1)
          020ab0752ad7f917c8c0e4ac6c80edf7
          # locked
          scm> (or False (- 1 1) 1)
          9815d8391210230341d3c0942b067539
          # locked
          scm> (or 4 True (/ 1 0))
          20bc71417eab0e038125723df967189e
          # locked
          scm> (or 0 1 2 'a)
          9815d8391210230341d3c0942b067539
          # locked
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          scm> (define x 0)
          x
          scm> (or (define x (+ x 1)) 3)
          x
          scm> x
          1
          scm> (or False (define x (+ x 1)))
          x
          scm> (or 2 (define x (+ x 1)))
          2
          scm> x
          2
          scm> (or False False)
          False
          scm> (or 'a False)
          a
          scm> (or (< 2 3) (> 2 3) 2 'a)
          True
          scm> (or (< 2 3) 2)
          True
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