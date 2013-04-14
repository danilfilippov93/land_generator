#ifndef Display_H
#define Display_H

class Display {
    public:
    Display();
    void OpenWindow();
    protected:
    void Draw();
    private:
    // Initializations
    void InitGLFW();
    void InitGLEW();
    void InitWindow();
    void UpdateLoop();
};

#endif