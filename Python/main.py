import numpy as np
from scipy import ndimage


def deform_vector_field(vector_field):
    #TODO
    a = 0


class VectorField:

    def __init__(self, size, parameter_dimensions, space_dimensions):
        self.size_ = size
        self.dimensions_ = parameter_dimensions+space_dimensions
        self.space_dimensions_ = space_dimensions
        a = []
        for i in range(self.dimensions_):
            a.append(size)
        a.append(space_dimensions)
        self.data_ = np.zeros(a)

    def critical_points(self):
        shape = np.shape(self.data_)
        zeros = np.zeros(shape)
        filter = [[1, 0, 1], [0, 0, 0], [1, 0, 1]]

        signed = np.sign(self.data_)
        binary_signed = np.maximum(signed, 0)

        positive_sum = np.array([[[ndimage.convolve(binary_signed[s, t, ..., i], filter, mode='nearest') for t in range(self.size_)] for s in range(self.size_)] for i in range(self.space_dimensions_)])
        positive_sum=np.mod(positive_sum,4)
        sign_change = np.where(positive_sum == 0, 0, 1)
        sign_change_sum = np.sum(sign_change, axis=0)

        print(sign_change_sum)


        #summed = np.convolve(binary_signed, [[1,0,1],[0,0,0],[1,0,1]], 'valid')
        #https: // numpy.org / doc / stable / reference / generated / numpy.diff.html
        #https: // docs.scipy.org / doc / scipy / reference / generated / scipy.ndimage.convolve.html
        #https: // stackoverflow.com / questions / 43123334 / multidimensional - convolution - in -python
        #https: // codereview.stackexchange.com / questions / 45458 / finding - a - zero - crossing - in -a - matrix

    def derivative(self):
        #TODO
        a = 0

    def jacobian(self):
        #TODO
        a = 0

    def feature_flow_field(self):
        #TODO
        a = 0


class Source:

    min_ = -2
    max_ = 2

    def __init__(self, size, source_type):
        self.source_type_ = source_type
        self.step_ = (self.max_-self.min_)/(size-1)
        if self.source_type_ == "2D2D":
            self.vector_field_ = VectorField(size, 2, 2)
        if self.source_type_ == "2D2DR":
            self.vector_field_ = VectorField(size, 1, 3)

    def normalize(self, index):
        return index*self.step_+self.min_

    def generate(self):
        iterator = np.nditer(self.vector_field_.data_[..., 0], flags=['multi_index'])
        for value in iterator:
            return_values = []
            if self.source_type_ == "2D2D":
                return_values.append(self.normalize(iterator.multi_index[2])*self.normalize(iterator.multi_index[2])-self.normalize(iterator.multi_index[0])-self.normalize(iterator.multi_index[1]))
                return_values.append(self.normalize(iterator.multi_index[3])+self.normalize(iterator.multi_index[0]))

            if self.source_type_ == "2D2DR":
                return_values.append(2*self.normalize(iterator.multi_index[2]))
                return_values.append(self.normalize(iterator.multi_index[2])*self.normalize(iterator.multi_index[2])-self.normalize(iterator.multi_index[0])-self.normalize(iterator.multi_index[1]))
                return_values.append(self.normalize(iterator.multi_index[3])+self.normalize(iterator.multi_index[0]))

            self.vector_field_.data_[iterator.multi_index] = return_values
            #print(self.vector_field_.data_[iterator.multi_index])


s = Source(5, "2D2D")
s.generate()
s.vector_field_.critical_points()


#https://numpy.org/doc/stable/reference/generated/numpy.fromfunction.html