def rpm(rpm_value):
	d = 7500 / 16
	t = int(rpm_value / d)
	out = ''
	for i in range(t):
		out += '#'
	return out

