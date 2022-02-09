#include <vector>

class MultiparameterDependentStructuredGridnD {
private:
    int field_dimensions_;
    int vector_dimension_;

    std::vector<double> mins_;
    std::vector<double> maxs_;
    std::vector<int> lengths_;
    std::vector<double> steps_;

    std::vector<std::vector<double>> data_;

    int amount_;

    void GenerateData(int id);

public:
    std::vector<double> GetIndicesByValues(std::vector<double> values);
    std::vector<double> GetVector(std::vector<double> indices);
    std::vector<double> GetVector(std::vector<int> indices);

    MultiparameterDependentStructuredGridnD(int field_dimensions, int vector_dimension, std::vector<double> mins, std::vector<double> maxs, std::vector<int> lengths, int function_id);
};