import numpy as np
import matplotlib
matplotlib.use('gtk3agg') 
# matplotlib.use('TkAgg')

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Define the function
x = np.linspace(-50, 50, 101)
y = np.linspace(-50, 50, 101)
x, y = np.meshgrid(x, y)
z = x + y

# Create the 3D plot
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

# Plot the surface
ax.plot_surface(x, y, z, cmap='viridis')

# Add labels
ax.set_xlabel('X-axis')
ax.set_ylabel('Y-axis')
ax.set_zlabel('Z-axis')
ax.set_title('3D Plot of z = x + y')

# Show the plot
plt.show()

# Let me know if you want to modify the function or add anything else! 🚀
