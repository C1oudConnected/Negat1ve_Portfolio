#pragma once

class Vector
{
private:
	//4D vector data (accessed by an operator[] to read & write).
	float m_data[4];

public:
	Vector();
	Vector(const float*);
	Vector(float, float, float, float);

	// Overloading operators to simplify the code.
	float&			operator[]	(unsigned char);		// Data access.
	const float&	operator()	(unsigned char) const;	// Data access(write only).
	Vector			operator+	(const Vector&) const;	// Summation with another vector.
	Vector&			operator+=	(const Vector&);		// Summation with assigning.
	Vector			operator-	(const Vector&) const;	// Subtracting.
	Vector&			operator-=	(const Vector&);		// Subtracting and assigning.
	Vector			operator*	(float)	const;			// Vector-number product.
	Vector&			operator*=	(float);				// Vector-number product with assigning.
	Vector			operator/	(float)	const;			// Vector-number division
	Vector&			operator/=	(float);				// Vector-number division with assigning.

	// Methods:

	Vector	proj(const Vector&);				// Get vector's projection on another vector;
	Vector&	nrmlz();								// Normalizes vector and gets it.
	Vector	nrmlzd() const;					// Gets normalized copy of the vector.
	float		dot(const Vector&) const;		// Dot-product.
	Vector	cross(const Vector&) const;	// Cross-product.
	float		L() const;							// Length of a vector.
	float 	L_sqr() const;						// Length (squared).
};
