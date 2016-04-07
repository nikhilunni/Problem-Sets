
""" Module that contains classes for the Markov model. """

import numpy as np
#from scipy.sparse import dok_matrix

class Markov(object):
    """ Constructor for a Markov model.  States are stored as integers

        state = 0, 1, 2, .. n-1

    where `n` is the number of states.

    Example Usage:

    >>> m = Markov(["a", "b"])          # Markov model with 2 states
    >>> m.state = "a"               # Set state to first state
    >>> m._transition_matrix = [[0, 1],    # Sets the transition matrix
    ...                         [1, 0]]
    >>> m.state()
    'a'
    >>> m.step()
    'b'
    >>> m.step()
    'a'
    """
    def __init__(self, states):
        """ Constructs a Markov model.

        Args:
            states: list of states
            mat: 2D array of transitions (n-by-n matrix) (default=None)

        Returns:
            Markov instance
        """
        self._states = states
        self._state2Index = {}
        for i, state in enumerate(states):
            self._state2Index[state] = i

        n = len(states)
        #self._transition_matrix = dok_matrix(np.zeros((n, n)))
        self._transition_matrix = np.zeros((n, n))

        self.state = None

    def step(self):
        """ Perform one update based on the transition matrix
        and the current state.

        Returns:
            new state
        """
        i = self._state2Index[self.state]

        # Get probability distribution given current state
        ps = np.array(self._transition_matrix[i])

        # Normalize
        ps /= np.sum(ps)

        # New state
        self.state = self._states[np.random.choice(len(self._states), p=ps)]
        return self.state

    def update_transition(self, next_state, prev_state):
        """ Adjusts the transition matrix given an extra sample. """
        next_index = self._state2Index[next_state]
        prev_index = self._state2Index[prev_state]
        self._transition_matrix[next_index][prev_index] += 1
