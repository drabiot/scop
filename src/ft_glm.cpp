/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glm.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:36:58 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/15 19:38:24 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glm.hpp"

// ---------------- VEC2 ----------------
vec2::vec2() : x(0), y(0) {}
vec2::vec2(float value) : x(value), y(value) {}
vec2::vec2(float newX, float newY) : x(newX), y(newY) {}
vec2::~vec2() {}
vec2 vec2::operator-(const vec2& other) const { return vec2(x - other.x, y - other.y); }

// ---------------- VEC3 ----------------
vec3::vec3() : x(0), y(0), z(0) {}
vec3::vec3(float value) : x(value), y(value), z(value) {}
vec3::vec3(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ) {}
vec3::~vec3() {}

// ---------------- VEC4 ----------------
vec4::vec4() : x(0), y(0), z(0), w(0) {}
vec4::vec4(float value) : x(value), y(value), z(value), w(value) {}
vec4::vec4(float newX, float newY, float newZ, float newW) : x(newX), y(newY), z(newZ), w(newW) {}
vec4::~vec4() {}

// ---------------- MAT3 ----------------
mat3::mat3() : c0(1,0,0), c1(0,1,0), c2(0,0,1) {}
mat3::mat3(float diagonal) : c0(diagonal,0,0), c1(0,diagonal,0), c2(0,0,diagonal) {}
mat3::mat3(const vec3& col0, const vec3& col1, const vec3& col2) : c0(col0), c1(col1), c2(col2) {}
mat3::mat3(const mat4& m) : c0(m.c0.x, m.c0.y, m.c0.z), c1(m.c1.x, m.c1.y, m.c1.z), c2(m.c2.x, m.c2.y, m.c2.z) {}
mat3::~mat3() {}

// ---------------- MAT4 ----------------
mat4::mat4() : c0(1,0,0,0), c1(0,1,0,0), c2(0,0,1,0), c3(0,0,0,1) {}
mat4::mat4(float diagonal) : c0(diagonal,0,0,0), c1(0,diagonal,0,0), c2(0,0,diagonal,0), c3(0,0,0,diagonal) {}
mat4::mat4(const vec4& A, const vec4& B, const vec4& C, const vec4& D) : c0(A), c1(B), c2(C), c3(D) {}
mat4::mat4(const mat3& m) : c0(m.c0.x,m.c0.y,m.c0.z,0), c1(m.c1.x,m.c1.y,m.c1.z,0), c2(m.c2.x,m.c2.y,m.c2.z,0), c3(0,0,0,1) {}
mat4::~mat4() {}

// ---------------- Operators ----------------
vec3	operator-(const vec3& v) { return vec3(-v.x,-v.y,-v.z); }
vec3	operator-(const vec3& a, const vec3& b) { return vec3(a.x-b.x,a.y-b.y,a.z-b.z); }
vec3	operator+(const vec3& a, const vec3& b) { return vec3(a.x+b.x,a.y+b.y,a.z+b.z); }
vec3	operator*(float s, const vec3& v) { return vec3(s*v.x,s*v.y,s*v.z); }
vec3&	operator+=(vec3& a, const vec3& b) { a.x+=b.x; a.y+=b.y; a.z+=b.z; return a; }

vec3	operator*(const mat3& m, const vec3& v) {
    return vec3(
        m.c0.x*v.x + m.c1.x*v.y + m.c2.x*v.z,
        m.c0.y*v.x + m.c1.y*v.y + m.c2.y*v.z,
        m.c0.z*v.x + m.c1.z*v.y + m.c2.z*v.z
    );
}

mat3	operator*(const mat3& a, const mat3& b) { return mat3(a*b.c0, a*b.c1, a*b.c2); }
vec4	operator*(const mat4& m, const vec4& v) { return vec4(m.c0.x*v.x+m.c1.x*v.y+m.c2.x*v.z+m.c3.x*v.w, m.c0.y*v.x+m.c1.y*v.y+m.c2.y*v.z+m.c3.y*v.w, m.c0.z*v.x+m.c1.z*v.y+m.c2.z*v.z+m.c3.z*v.w, m.c0.w*v.x+m.c1.w*v.y+m.c2.w*v.z+m.c3.w*v.w); }
mat4	operator*(const mat4& a, const mat4& b) { return mat4(a*b.c0,a*b.c1,a*b.c2,a*b.c3); }

// ---------------- Math functions ----------------
float	radians(float deg) { return deg * 0.017453292519943295f; }
float	abs(float v) { return v<0?-v:v; }
vec3	abs(const vec3& v) { return vec3(abs(v.x), abs(v.y), abs(v.z)); }
float	max(float a,float b){return a>b?a:b;}
float	min(float a,float b){return a<=b?a:b;}
vec3	normalize(const vec3& v){float len=sqrt(v.x*v.x+v.y*v.y+v.z*v.z);return len==0?vec3(0):vec3(v.x/len,v.y/len,v.z/len);}
vec3	cross(const vec3& a,const vec3& b){return vec3(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);}
float	dot(const vec3& a,const vec3& b){return a.x*b.x+a.y*b.y+a.z*b.z;}
float	angle(const vec3& a,const vec3& b){float d=dot(normalize(a),normalize(b));d=max(-1.f,min(1.f,d));return acos(d);}

// ---------------- GLM-like functions ----------------
const float*	value_ptr(const mat4& m){return &m.c0.x;}
const float*	value_ptr(const vec3& v){return &v.x;}

mat4	translate(const mat4& m, const vec3& v){mat4 r=m;r.c3.x+=v.x;r.c3.y+=v.y;r.c3.z+=v.z;return r;}
mat4	translate(const vec3& v){mat4 r(1);r.c3.x+=v.x;r.c3.y+=v.y;r.c3.z+=v.z;return r;}

vec3	rotate(const vec3& v, float angle, const vec3& axis){
    vec3 a=normalize(axis); float c=cos(angle), s=sin(angle), t=1-c;
    return vec3((t*a.x*a.x+c)*v.x+(t*a.x*a.y-s*a.z)*v.y+(t*a.x*a.z+s*a.y)*v.z,
                (t*a.x*a.y+s*a.z)*v.x+(t*a.y*a.y+c)*v.y+(t*a.y*a.z-s*a.x)*v.z,
                (t*a.x*a.z-s*a.y)*v.x+(t*a.y*a.z+s*a.x)*v.y+(t*a.z*a.z+c)*v.z);
}

mat4	rotate(float angle, const vec3& axis){
    vec3 a=normalize(axis); float c=cos(angle), s=sin(angle), t=1-c;
    return mat4(vec4(t*a.x*a.x+c,t*a.x*a.y+s*a.z,t*a.x*a.z-s*a.y,0),
                vec4(t*a.x*a.y-s*a.z,t*a.y*a.y+c,t*a.y*a.z+s*a.x,0),
                vec4(t*a.x*a.z+s*a.y,t*a.y*a.z-s*a.x,t*a.z*a.z+c,0),
                vec4(0,0,0,1));
}

mat4	rotate(const mat4& m,float angle,const vec3& axis){return m*rotate(angle,axis);}

mat4	lookAt(const vec3& eye,const vec3& center,const vec3& up){
    vec3 f=normalize(center-eye);
    vec3 s=normalize(cross(f,up));
    vec3 u=cross(s,f);
    mat4 r(1.0f);
    r.c0=vec4(s.x,u.x,-f.x,0); r.c1=vec4(s.y,u.y,-f.y,0); r.c2=vec4(s.z,u.z,-f.z,0);
    r.c3=vec4(-dot(s,eye),-dot(u,eye),dot(f,eye),1);
    return r;
}

mat4	perspective(float fov,float aspect,float near,float far){
    float f=1.0f/tan(fov*0.5f); mat4 r(0.0f);
    r.c0.x=f/aspect; r.c1.y=f; r.c2.z=(far+near)/(near-far); r.c2.w=-1.f; r.c3.z=(2.f*far*near)/(near-far);
    return r;
}

mat4	ortho(float l,float r,float b,float t,float n,float f){
    mat4 m(1.0f); m.c0.x=2.f/(r-l); m.c1.y=2.f/(t-b); m.c2.z=-2.f/(f-n); m.c3.x=-(r+l)/(r-l); m.c3.y=-(t+b)/(t-b); m.c3.z=-(f+n)/(f-n);
    return m;
}

