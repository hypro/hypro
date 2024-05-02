import numpy as np
import pandas as pd
import matplotlib.pyplot as plt 

from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler

def read_data():
    sonar_df = pd.read_csv('./examples/nn_benchmarks/properties/sonar/sonar.csv', header=None)
    return sonar_df

def analyse_data(sonar_df):
    # print(sonar_df.head())

    data = sonar_df.iloc[ :, sonar_df.columns != 60].to_numpy()
    labels = sonar_df.iloc[:, 60].to_numpy()

    std_deviation = np.std(data, axis=0)
    print('Standard deviatiions:', std_deviation)
    print('Standard deviation shape:', std_deviation.shape)
    print('Min standard deviation:', min(std_deviation))

    # print(data)
    # print(labels)

    pca = PCA(n_components=2)
    pca.fit(data)

    # print(data.shape)
    # print(pca.components_.shape)

    data = StandardScaler().fit_transform(data)

    # final_data = np.matmul(data, pca.components_.T)
    final_data = pca.transform(data)

    data_x = final_data[:, 0]
    data_y = final_data[:, 1]

    for g in np.unique(labels):
        i = np.where(labels == g)
        plt.scatter(data_x[i], data_y[i], label=g)
    plt.legend()
    plt.show()

if __name__=='__main__':
    sonar_df = read_data()
    analyse_data(sonar_df)