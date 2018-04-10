#ifndef TEXTURE_H
#define TEXTURE_H


class Texture {
    public:
        Texture(int _id, int _steps);

        int getId() { return id; }
        void setId( int val) { id = val; }
        int getSteps() { return steps; }
        void setSteps(int val) { steps = val; }
        int getCurrentStep() { return currentStep; }
        void incrementStep(double animationFactor) {
            if(currentStep < ((steps-1)*animationFactor)) currentStep++;
            else currentStep = 0;
        }
        void incrementStep() {
            if(currentStep < (steps-1)) currentStep++;
            else currentStep = 0;
        }

    protected:

    private:
        int id;
        int steps;
        int currentStep;
};

#endif // TEXTURE_H
