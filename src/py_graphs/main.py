import pandas as pd
import matplotlib.pyplot as plt

filenames = {
    'standard_random': 'standard_random.csv',
    'hybrid_random': 'hybrid_random.csv',
    'standard_reversed': 'standard_reversed.csv',
    'hybrid_reversed': 'hybrid_reversed.csv',
    'standard_almost': 'standard_almost_sorted.csv',
    'hybrid_almost': 'hybrid_almost_sorted.csv'
}

data = {key: pd.read_csv(filename) for key, filename in filenames.items()}


# first
plt.figure(figsize=(12, 8))

plt.plot(data['standard_random']['N'], data['standard_random']['AverageTime_ms'],
         label='Стандартная сортировка слиянием', color='blue')
plt.plot(data['hybrid_random']['N'], data['hybrid_random']['AverageTime_ms'],
         label='Гибридная (Merge + Insertion) сортировка', color='green')

plt.title('График 1: Производительность на случайных данных')
plt.xlabel('Размер массива (N)')
plt.ylabel('Среднее время выполнения (мс)')
plt.grid(True)
plt.legend()
plt.tight_layout()

plt.show()


# second
plt.figure(figsize=(12, 8))

plt.plot(data['standard_reversed']['N'], data['standard_reversed']['AverageTime_ms'],
         label='Стандартная сортировка слиянием', color='blue')
plt.plot(data['hybrid_reversed']['N'], data['hybrid_reversed']['AverageTime_ms'],
         label='Гибридная (Merge + Insertion) сортировка', color='red')

plt.title('График 2: Производительность на обратно отсортированных данных')
plt.xlabel('Размер массива (N)')
plt.ylabel('Среднее время выполнения (мс)')
plt.grid(True)
plt.legend()
plt.tight_layout()

plt.show()


# third
plt.figure(figsize=(12, 8))

plt.plot(data['standard_almost']['N'], data['standard_almost']['AverageTime_ms'],
         label='Стандартная сортировка слиянием', color='blue')
plt.plot(data['hybrid_almost']['N'], data['hybrid_almost']['AverageTime_ms'],
         label='Гибридная (Merge + Insertion) сортировка', color='orange')

plt.title('График 3: Производительность на почти отсортированных данных')
plt.xlabel('Размер массива (N)')
plt.ylabel('Среднее время выполнения (мс)')
plt.grid(True)
plt.legend()
plt.tight_layout()

plt.show()