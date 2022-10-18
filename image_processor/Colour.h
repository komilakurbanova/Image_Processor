struct MulColour{
    int r;
    int b;
    int g;
    MulColour(int r_set, int g_set, int b_set);
    MulColour operator+(const MulColour& other);
    void operator+=(const MulColour& other);
};

struct Colour {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    Colour();
    Colour(unsigned char r_set, unsigned char g_set, unsigned char b_set);
    Colour(const Colour& other);
    ~Colour();
    MulColour operator*(int mul);
};
