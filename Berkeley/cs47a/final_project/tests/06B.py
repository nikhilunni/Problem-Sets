test = {
  'name': 'Question 6',
  'partner': 1,
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'answer': '252961b4cb911638137d5a06b8fd4276',
          'choices': [
            r"""
            Pair('quote', Pair(A, nil)), where:
                A is the quoted expression
            """,
            r"""
            [A], where:
                A is the quoted expression
            """,
            r"""
            Pair(A, nil), where:
                A is the quoted expression
            """,
            r"""
            A, where:
                A is the quoted expression
            """
          ],
          'hidden': False,
          'locked': True,
          'question': 'What is the structure of the expressions argument to do_quote_form?'
        }
      ],
      'scored': False,
      'type': 'concept'
    },
    {
      'cases': [
        {
          'code': r"""
          scm> (quote hello)
          3c8aeeea999a71da894f0f8c97512455
          # locked
          scm> 'hello
          3c8aeeea999a71da894f0f8c97512455
          # locked
          scm> ''hello
          1786fd0b918ccc2844e85a6c27b13e68
          # locked
          # choice: (quote hello)
          # choice: hello
          # choice: (hello)
          # choice: (quote (quote (hello)))
          scm> (quote (1 2))
          74c628f8c673bdae43f820028ee11aef
          # locked
          scm> '(1 2)
          74c628f8c673bdae43f820028ee11aef
          # locked
          scm> (quote (1 . 2))
          61a5905669b1b2d0afd68f9a356801d3
          # locked
          scm> '(1 . (2))
          74c628f8c673bdae43f820028ee11aef
          # locked
          scm> (car '(1 2 3))
          7107157269a542fea41c45a208299f75
          # locked
          scm> (cdr '(1 2))
          68c63327e3712cbea6fbd7e9a2602b64
          # locked
          scm> (car (car '((1))))
          7107157269a542fea41c45a208299f75
          # locked
          scm> (quote 3)
          5d8831cb01cb0c9d130940fa232fd534
          # locked
          scm> (eval (cons 'car '('(4 2))))
          20bc71417eab0e038125723df967189e
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