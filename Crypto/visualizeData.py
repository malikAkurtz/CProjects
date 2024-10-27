import matplotlib.pyplot as plt
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D

def graphData():
    # Load and clean up data
    data = pd.read_csv("results.csv")
    data.columns = data.columns.str.strip()
    print(data.head())

    # Create a 3D plot
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Define the axes: X for K, Y for Success Rate, Z for BER
    x = data['K']
    y = data['Success Rate']
    z = data['BER']

    # Plotting each point in 3D
    ax.scatter(x, y, z, color='b', marker="o", s=50, label="Data Points")

    # Label the axes
    ax.set_xlabel("Constraint Length (K)")
    ax.set_ylabel("Success Rate (%)")
    ax.set_zlabel("Bit Error Rate (BER)")

    # Set plot title and legend
    ax.set_title("3D Plot of Success Rate and BER vs Constraint Length")
    ax.legend()

    # Show the plot
    plt.show()

def main():
    graphData()
    return 0

main()
