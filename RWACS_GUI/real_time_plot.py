import matplotlib.pyplot as plt
import numpy as np


class RealTimePlot():
    """A class used to easly plot csv data in real time
    """

    def __init__(self, nrows: int, ncols: int, x_lim: int):

        if (nrows <= 0 or ncols <= 0):
            raise ValueError("ncols and nrows can't be equal to 0 or less")

        y_data = np.array(np.zeros([x_lim]))

        plt.ion()

        self.__x_lim = x_lim
        self.__lines = []
        self.__y_data_list = []

        self.__fig, self.__axs = plt.subplots(nrows, ncols)

        for single_ax in self.__traverse(self.__axs):
            self.__y_data_list.append(y_data)
            line, = single_ax.plot(y_data)
            self.__lines.append(line)

    def update(self, new_y_samples: list):
        """
        Update plots with new samples

        Args:
            new_y_samples (list): a list of samples to update the plot with

        Raises:
            ValueError: if new samples length differs from what has been previously declared
        """
        if len(new_y_samples) != len(self.__y_data_list):
            raise ValueError("incorrect y_data lenght")

        for i, _ in enumerate(self.__y_data_list):
            self.__y_data_list[i] = np.append(
                self.__y_data_list[i], new_y_samples[i])
            self.__y_data_list[i] = self.__y_data_list[i][1:self.__x_lim+1]
            self.__lines[i].set_ydata(self.__y_data_list[i])

        for single_ax in self.__traverse(self.__axs):
            single_ax.relim()
            single_ax.autoscale_view()

        self.__fig.canvas.draw()
        self.__fig.canvas.flush_events()

    def __traverse(self, values, tree_types=(list, tuple, np.ndarray)):
        if isinstance(values, tree_types):
            for value in values:
                for subvalue in self.__traverse(value, tree_types):
                    yield subvalue
        else:
            yield values
