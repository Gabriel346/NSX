#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include <QMatrix4x4>

class Transform3D
{
   // Q_GADGET

public:
    Transform3D();
    Transform3D(QVector3D pos, QQuaternion rot, QVector3D scl);

    ~Transform3D() = default;
    Transform3D(const Transform3D &) = default;
    Transform3D &operator=(const Transform3D &) = default;

    void translate(const QVector3D &dt);
    void translate(float dx, float dy, float dz);
    void scale(const QVector3D &ds);
    void scale(float dx, float dy, float dz);
    void scale(float factor);
    void rotate(const QQuaternion &dr);
    void rotate(float angle, const QVector3D &axis);
    void rotate(float angle, float ax, float ay, float az);

    void setTranslation(const QVector3D &t);
    void setTranslation(float x, float y, float z);
    void setScale(const QVector3D &s);
    void setScale(float x, float y, float z);
    void setScale(float k);
    void setRotation(const QQuaternion &r);
    void setRotation(float angle, const QVector3D &axis);
    void setRotation(float angle, float ax, float ay, float az);
    void setMatrix(const QMatrix4x4 &in);

    const QVector3D& translation() const;
    const QQuaternion& rotation() const;
    const QVector3D& scale() const;
    const QMatrix4x4& toMatrix();

    //TODO operator
    Transform3D& operator*=(const Transform3D& t);
    //TOO use a library

private:
      QMatrix4x4 _matrix;
      QQuaternion _rotation; //rot
      QVector3D _translation; //pos
      QVector3D _scale;
      bool _modified;


    friend const Transform3D operator*(const Transform3D& t1, const Transform3D& t2);
};

inline Transform3D::Transform3D() : _scale(1.0f, 1.0f, 1.0f),  _modified(true) {}
inline Transform3D::Transform3D(QVector3D pos, QQuaternion rot, QVector3D scl) : _modified(true), _translation(pos), _rotation(rot), _scale(scl) {}

inline void Transform3D::translate(float dx, float dy,float dz) { translate(QVector3D(dx, dy, dz)); }
inline void Transform3D::scale(float dx, float dy,float dz) { scale(QVector3D(dx, dy, dz)); }
inline void Transform3D::scale(float factor) { scale(QVector3D(factor, factor, factor)); }
inline void Transform3D::rotate(float angle, const QVector3D &axis) { rotate(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Transform3D::rotate(float angle, float ax, float ay,float az) { rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }

inline void Transform3D::setTranslation(float x, float y, float z) { setTranslation(QVector3D(x, y, z)); }
inline void Transform3D::setScale(float x, float y, float z) { setScale(QVector3D(x, y, z)); }
inline void Transform3D::setScale(float k) { setScale(QVector3D(k, k, k)); }
inline void Transform3D::setRotation(float angle, const QVector3D &axis) { setRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Transform3D::setRotation(float angle, float ax, float ay, float az) { setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }
inline void Transform3D::setMatrix(const QMatrix4x4 &in) {
    //TODO decomposition
    _translation = in.column(3).toVector3D();
    //_scale =  lenght of the 3 columns vector sx = |(m0.0, m0.1, m0.2)|
    //rotation = remove translation, remove scale (m0.0, m0.1, m0.2)/sx... get rotation matrix  ?
    _matrix = in;
}

inline const QVector3D& Transform3D::translation() const { return _translation; }
inline const QVector3D& Transform3D::scale() const { return _scale; }
inline const QQuaternion& Transform3D::rotation() const { return _rotation; }

//const Transform3D operator+(const Transform3D t, const QVector3D v) {
//    return Transform3D();
//}
const Transform3D operator*(const Transform3D& t1, const Transform3D& t2);


Q_DECLARE_METATYPE(Transform3D*)
Q_DECLARE_METATYPE(Transform3D)

#endif // TRANSFORM3D_H
