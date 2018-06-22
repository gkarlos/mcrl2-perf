import matplotlib.pyplot as plt

unique_args = [1681, 3476, 1253, 1692, 2127, 2683, 3256, 3657, 4444, 4767, 5164]
unique_args = [t / 1000.0 for t in unique_args]
fixed_args = [391, 4037, 4614, 4987, 5143, 5784, 6552, 7084, 7453, 7916, 8370]
fixed_args = [t / 1000.0 for t in fixed_args]

plt.plot(unique_args, label="unique_args")
plt.plot(fixed_args, label="fixed_args")
plt.xticks(range(len(unique_args)))
plt.ylabel(u'\u03bcs')
plt.xlabel('arity')
plt.grid(zorder=1, linestyle='dotted')
plt.legend()
plt.title('ATerm creation depth 1, variable arity')
plt.savefig("term_creation_depth_1_variable_arity")
