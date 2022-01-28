#pragma once
#include "HasInput.h"
#include "HasOutput.h"
template<class InputType1, class InputType2, class OutputType> class Filter : public HasInput<InputType1>, public HasOutput<OutputType>{

};