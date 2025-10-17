import matplotlib.pyplot as plt
import re

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

# Convert to float lists
p1, p2, p3, pn1, pn2, pn3, pn4 = [], [], [], [], [], [], []
for m in matches:
    vals = list(map(float, m))
    p1.append(vals[0])
    p2.append(vals[1])
    p3.append(vals[2])
    pn1.append(vals[3])
    pn2.append(vals[4])
    pn3.append(vals[5])
    pn4.append(vals[6])

# X-axis for agents
x = list(range(1, len(p1)+1))

# Plot all seven lines
plt.figure(figsize=(12, 6))
plt.plot(x, p1,  label="p1",  marker='o', linestyle='-', alpha=0.7)
plt.plot(x, p2,  label="p2",  marker='s', linestyle='-', alpha=0.7)
plt.plot(x, p3,  label="p3",  marker='^', linestyle='-', alpha=0.7)
plt.plot(x, pn1, label="pn1 (after CC)", marker='x', linestyle='-', alpha=0.7)
plt.plot(x, pn2, label="pn2 (after CD)", marker='d', linestyle='-', alpha=0.7)
plt.plot(x, pn3, label="pn3 (after DC)", marker='v', linestyle='-', alpha=0.7)
plt.plot(x, pn4, label="pn4 (after DD)", marker='*', linestyle='-', alpha=0.7)

# Chart details
plt.title("Agent Probabilities (p1, p2, p3, pn1–pn4)")
plt.xlabel("Agent Index")
plt.ylabel("Probability p")
plt.ylim(0, 1)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.tight_layout()
plt.show()
