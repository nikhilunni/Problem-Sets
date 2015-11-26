test = {
  'name': 'Question 5',
  'partner': 0,
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'answer': 'b8204d82bf3c1d4f24f6eca40b70a622',
          'choices': [
            r"""
            Pair(A, Pair(B, nil)), where:
                A is the symbol being bound,
                B is an expression whose value should be bound to A
            """,
            r"""
            Pair(A, Pair(B, nil)), where:
                A is the symbol being bound,
                B is the value that should be bound to A
            """,
            r"""
            Pair(A, B), where:
                A is the symbol being bound,
                B is the value that should be bound to A
            """,
            r"""
            Pair(A, B), where:
                A is the symbol being bound,
                B is an expression whose value should be bound to A
            """,
            r"""
            Pair('define', Pair(A, Pair(B, nil))), where:
                A is the symbol being bound,
                B is an expression whose value should be bound to A
            """
          ],
          'hidden': False,
          'locked': True,
          'question': 'What is the structure of the expressions argument to do_define_form?'
        },
        {
          'answer': 'a48fa38f68497d2e422dd31c397eaf76',
          'choices': [
            'make_call_frame',
            'define',
            'lookup',
            'bindings'
          ],
          'hidden': False,
          'locked': True,
          'question': r"""
          What method of a Frame instance will bind
          a value to a symbol in that frame?
          """
        }
      ],
      'scored': False,
      'type': 'concept'
    },
    {
      'cases': [
        {
          'code': r"""
          scm> (define size 2)
          3cef6153a5a93752178b1028ce91fc84
          # locked
          scm> size
          9ea224e62b219a1ee61849f282da5e65
          # locked
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          scm> (define x (+ 2 3))
          57775d5ff999af0ee4cbfa3aa0507be8
          # locked
          scm> x
          020ab0752ad7f917c8c0e4ac6c80edf7
          # locked
          scm> (define x (+ 2 7))
          57775d5ff999af0ee4cbfa3aa0507be8
          # locked
          scm> x
          a7d60ae9b0b81fce195ed5b13796867a
          # locked
          scm> (eval (define tau 6.28))
          425e5e1cf58a1ce2072411c7c0f91257
          # locked
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          scm> (define pi 3.14159)
          pi
          scm> (define radius 10)
          radius
          scm> (define area (* pi (* radius radius)))
          area
          scm> area
          314.159
          scm> (define 0 1)
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