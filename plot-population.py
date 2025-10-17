import matplotlib.pyplot as plt
import re
import numpy as np

# Paste your population text here
text = """Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.73 p3=0.95. pn1=1.00 pn2=0.45 pn3=0.18 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.68 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.55. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.95. pn1=1.00 pn2=0.50 pn3=0.18 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.95. pn1=1.00 pn2=0.45 pn3=0.18 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.85. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.73 p3=0.95. pn1=1.00 pn2=0.45 pn3=0.18 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.73 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.00 pn4=0.50. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.85. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.40 p2=0.73 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.85. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.13 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.50 p2=0.73 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.50. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.73 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.00 pn4=0.50. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.85. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.68 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.55. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.85. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.73 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.68 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.55. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.73 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.00 pn4=0.50. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.30. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.68 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.55. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.73 p3=0.95. pn1=1.00 pn2=0.45 pn3=0.18 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.73 p3=0.90. pn1=0.95 pn2=0.45 pn3=0.13 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.68 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.55. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.73 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.00 pn4=0.50. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.68 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.55. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.85. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.68 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.55. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.73 p3=0.90. pn1=0.95 pn2=0.45 pn3=0.13 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.73 p3=0.95. pn1=1.00 pn2=0.45 pn3=0.18 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=0.95 pn2=0.45 pn3=0.13 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.50 p2=0.73 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.50. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.40 p2=0.73 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.95. pn1=0.95 pn2=0.45 pn3=0.18 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.73 p3=0.95. pn1=1.00 pn2=0.45 pn3=0.18 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.78 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.03 pn4=0.45. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.25 p2=0.68 p3=0.90. pn1=1.00 pn2=0.40 pn3=0.08 pn4=0.35. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.45 p2=0.73 p3=1.00. pn1=1.00 pn2=0.45 pn3=0.00 pn4=0.50. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.63 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
Agent: x, y: 1, 6. p1=0.30 p2=0.68 p3=0.90. pn1=1.00 pn2=0.45 pn3=0.08 pn4=0.40. accumAvgPayoff=0.00. roundsPlayed: 0.
"""

# Regex pattern to extract p1, p2, p3, pn1–pn4 values
pattern = (r"p1=(\d+\.\d+)\s+p2=(\d+\.\d+)\s+p3=(\d+\.\d+)\.\s+"
           r"pn1=(\d+\.\d+)\s+pn2=(\d+\.\d+)\s+pn3=(\d+\.\d+)\s+pn4=(\d+\.\d+)")

matches = re.findall(pattern, text)

# Convert to float arrays
values = np.array([[float(v) for v in match] for match in matches])

# Compute averages across all agents
avg_values = values.mean(axis=0)

# Labels for all probabilities
labels = ['p1', 'p2', 'p3', 'pn1 (after CC)', 'pn2 (after CD)', 'pn3 (after DC)', 'pn4 (after DD)']

# Plot bar chart
plt.figure(figsize=(8,5))
plt.bar(labels, avg_values, color='skyblue')
plt.ylim(0, 1)
plt.title("Average Probability of Cooperation (All States)")
plt.ylabel("p (Probability of Cooperation)")
plt.xticks(rotation=30, ha='right')
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()

# Print numeric results
for lbl, val in zip(labels, avg_values):
    print(f"{lbl}: {val:.2f}")
