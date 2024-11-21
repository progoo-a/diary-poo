#include <vector>

class Bessel {
    double cutoff;
    double sampleRate;

    // Direct form II coefficients
    double a1, a2, b0, b1, b2;

public:
    Bessel(double cutoff, double sampleRate);
    ~Bessel();
    auto filter(std::vector<double>& data);

    auto operator()(std::vector<double>&data) {
        return filter(input);
    }

    void reset();

private:
    void calculateCoefficients() {
        // ...
    }
};

int main() {
    Bessel bessel(4, 1000, 44100);
    std::vector<double> data;
    bessel(data);
    bessel.changeSamplingFrequency(24100);
    
}