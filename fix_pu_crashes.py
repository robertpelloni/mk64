import os

filepath = "src/racing/math_util.c"
with open(filepath, 'r') as f:
    content = f.read()

# I see the clamps are already there!
# "if (fixed_f > 2147483647.0f) fixed_f = 2147483647.0f;"
# Is there another place that needs it?
