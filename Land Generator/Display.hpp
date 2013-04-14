#ifndef Display_H
#define Display_H
class Triangle;
class Display {
    public:
    Display();
    void OpenWindow();
	Triangle *triangle;

    protected:
    void Draw();

    private:
    // Initializations
    void InitGLFW();
    void InitGLEW();
    void InitWindow();
	// Update
    void UpdateLoop();
};

#endif