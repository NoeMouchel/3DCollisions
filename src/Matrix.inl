using namespace ToolBox;

//====================================== Matrix Functions ======================================

inline Mat4x4 ToolBox::mat4x4Identity()
{
    return {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f,
    };
}

inline Mat4x4 ToolBox::operator*(const float& a, const Mat4x4& b)
{
	Mat4x4 to_return = mat4x4Identity();

	for (int i = 0; i < 16; i++)
	{
		to_return.e[i] = b.e[i] * a;
	}

    return to_return;
}

//  Mat4x4 x Vector4f
inline Vector4f ToolBox::operator*(const Mat4x4& m, const Vector4f& v)
{
    Vector4f to_return = {1, 1, 1, 1};

    for (int i = 0; i < 4; ++i)
    {
        float sum = 0.0f;
        for (int j = 0; j < 4; ++j)
            sum += v.e[j] * m.c[j].e[i];
        to_return.e[i] = sum;
    }
    return to_return;
}

//  Mat4x4 x Mat4x4
inline Mat4x4 ToolBox::operator*(const Mat4x4& a, const Mat4x4& b)
{
    Mat4x4 mat = mat4x4Identity();
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
            for (int inner = 0; inner < 4; inner++)
                mat.c[col].e[row] += a.c[inner].e[row] * b.c[col].e[inner];
    return mat;
}


inline Mat4x4 ToolBox::operator+(const Mat4x4& a, const Mat4x4& b)
{
	Mat4x4 mat = mat4x4Identity();
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
                mat.c[col].e[row] += a.c[col].e[row] + b.c[col].e[row];
    return mat;
}


