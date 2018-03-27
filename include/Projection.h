#ifndef PROJECTION_H
#define PROJECTION_H


class Projection
{
    public:
        Projection(double _minValue, double _maxValue);

        double getMin() { return minValue; }
        void setMin(double val) { minValue = val; }
        double getMax() { return maxValue; }
        void getMax(double val) { maxValue = val; }

        bool overlaps(Projection p);
    protected:

    private:
        double minValue;
        double maxValue;
};

#endif // PROJECTION_H
