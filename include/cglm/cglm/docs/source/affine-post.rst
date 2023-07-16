.. default-domain:: C

3D Affine Transforms (post)
================================================================================

Post transfrom functions are similar to pre Transform functions except order of application is reversed.
Post Transform functions are applied after the object is transformed with given (model matrix) transfrom.

Ther are named af

Table of contents (click to go):
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Functions:

1. :c:func:`glm_translated_to`
#. :c:func:`glm_translated`
#. :c:func:`glm_translated_x`
#. :c:func:`glm_translated_y`
#. :c:func:`glm_translated_z`
#. :c:func:`glm_rotated_x`
#. :c:func:`glm_rotated_y`
#. :c:func:`glm_rotated_z`
#. :c:func:`glm_rotated`
#. :c:func:`glm_rotated_at`
#. :c:func:`glm_spinned`

Functions documentation
~~~~~~~~~~~~~~~~~~~~~~~

.. c:function:: void  glm_translated_to(mat4 m, vec3 v, mat4 dest)

    translate existing Transform matrix by *v* vector and store result in dest

    Parameters:
      | *[in]*  **m**    affine transfrom
      | *[in]*  **v**    translate vector [x, y, z]
      | *[out]* **dest** translated matrix

.. c:function:: void  glm_translated(mat4 m, vec3 v)

    translate existing Transform matrix by *v* vector
    and stores result in same matrix

    Parameters:
      | *[in, out]* **m**  affine transfrom
      | *[in]*      **v**  translate vector [x, y, z]

.. c:function:: void  glm_translated_x(mat4 m, float x)

    translate existing Transform matrix by x factor

    Parameters:
      | *[in, out]* **m**  affine transfrom
      | *[in]*      **v**  x factor

.. c:function:: void  glm_translated_y(mat4 m, float y)

    translate existing Transform matrix by *y* factor

    Parameters:
      | *[in, out]* **m**  affine transfrom
      | *[in]*      **v**  y factor

.. c:function:: void  glm_translated_z(mat4 m, float z)

    translate existing Transform matrix by *z* factor

    Parameters:
      | *[in, out]* **m**  affine transfrom
      | *[in]*      **v**  z factor

.. c:function:: void  glm_rotated_x(mat4 m, float angle, mat4 dest)

    rotate existing Transform matrix around X axis by angle
    and store result in dest

    Parameters:
      | *[in]*  **m**     affine transfrom
      | *[in]*  **angle** angle (radians)
      | *[out]* **dest**  rotated matrix

.. c:function:: void  glm_rotated_y(mat4 m, float angle, mat4 dest)

    rotate existing Transform matrix around Y axis by angle
    and store result in dest

    Parameters:
      | *[in]*  **m**     affine transfrom
      | *[in]*  **angle** angle (radians)
      | *[out]* **dest**  rotated matrix

.. c:function:: void  glm_rotated_z(mat4 m, float angle, mat4 dest)

    rotate existing Transform matrix around Z axis by angle
    and store result in dest

    Parameters:
      | *[in]*  **m**     affine transfrom
      | *[in]*  **angle** angle (radians)
      | *[out]* **dest**  rotated matrix

.. c:function:: void  glm_rotated(mat4 m, float angle, vec3 axis)

    rotate existing Transform matrix around Z axis by angle and axis

    Parameters:
      | *[in, out]* **m**     affine transfrom
      | *[in]*      **angle** angle (radians)
      | *[in]*      **axis**  axis

.. c:function:: void  glm_rotated_at(mat4 m, vec3 pivot, float angle, vec3 axis)

    rotate existing Transform around given axis by angle at given pivot point (rotation center)

    Parameters:
      | *[in, out]* **m**     affine transfrom
      | *[in]*      **pivot** pivot, anchor point, rotation center
      | *[in]*      **angle** angle (radians)
      | *[in]*      **axis**  axis

.. c:function:: void  glm_spinned(mat4 m, float angle, vec3 axis)

    | rotate existing Transform matrix around given axis by angle around self (doesn't affected by position)

    Parameters:
      | *[in, out]* **m**     affine transfrom
      | *[in]*      **angle** angle (radians)
      | *[in]*      **axis**  axis
