//
//  Utility_3D.h
//  //some 3D utility function for converting mousePos to OpenGL world. From Paul Houx and Stephen Schieberl
//

#ifndef Game_HotOrCold_Utility_3D_h
#define Game_HotOrCold_Utility_3D_h

#include "cinder/app/AppNative.h"

class Utility_3D
{
    public:
    Matrix44f   mModelView;
    Matrix44f   mProjection;
    Area        mViewport;
    Rectf       mWindowSize;
    
    Utility_3D(){}
    ~Utility_3D(){}
    
    // Convert mouse position to 3D
    ci::Vec3f screenToWorld(const Vec2i & point)
    {
        // Find near and far plane intersections
        Vec3f point3f = Vec3f((float)point.x, mWindowSize.getHeight() * 0.5f - (float)point.y, 0.0f);
        Vec3f nearPlane = unproject(point3f);
        Vec3f farPlane = unproject(Vec3f(point3f.x, point3f.y, 1.0f));
        
        // Calculate X, Y and return point
        float theta = (0.0f - nearPlane.z) / (farPlane.z - nearPlane.z);
        return Vec3f(
                     nearPlane.x + theta * (farPlane.x - nearPlane.x),
                     nearPlane.y + theta * (farPlane.y - nearPlane.y),
                     0.0f
                     );
        
    }

    //Unproject a coordinate back to to camera
    ci::Vec3f unproject(const Vec3f & point)
    {
        // Find the inverse Modelview-Projection-Matrix
        Matrix44f mInvMVP = mProjection * mModelView;
        mInvMVP.invert();
        
        // Transform to normalized coordinates in the range [-1, 1]
        Vec4f pointNormal;
        pointNormal.x = (point.x - mViewport.getX1()) / mViewport.getWidth() * 2.0f - 1.0f;
        pointNormal.y = (point.y - mViewport.getY1()) / mViewport.getHeight() * 2.0f;
        pointNormal.z = 2.0f * point.z - 1.0f;
        pointNormal.w = 1.0f;
        
        // Find the object's coordinates
        Vec4f pointCoord = mInvMVP * pointNormal;
        if (pointCoord.w != 0.0f)
            pointCoord.w = 1.0f / pointCoord.w;
        
        // Return coordinate
        return Vec3f(
                     pointCoord.x * pointCoord.w,
                     pointCoord.y * pointCoord.w, 
                     pointCoord.z * pointCoord.w
                     );
        
    }
    
    void setModelView(const Matrix44f modelView)
    {
        mModelView = modelView;
    }
    
    void setProjection(const Matrix44f projection)
    {
        mProjection = projection;
    }
    
    void setViewport(const Area viewPort)
    {
        mViewport = viewPort;
    }
    
    void setWindowSize(const Rectf windowSize)
    {
        mWindowSize = windowSize;
    }
};

#endif
