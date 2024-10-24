import matplotlib.pyplot as plt
import pandas as pd

def graphData():
    data = pd.read_csv("results.csv")
    data.columns = data.columns.str.strip()
    print(data.head())

    plt.plot(data['K'], data['Success Rate'], marker = "o")
    plt.xlabel("Constraint Length (k)")
    plt.ylabel("Success Rate (%)")
    plt.title("Success Rate vs Constraint Length")
    plt.grid(True)
    plt.show()


def main():
    graphData();

    return 0;

main();