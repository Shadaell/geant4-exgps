/***************************************************************************
 *  Copyright (C) 2011-2012 Bogdan Maslovskiy                              *
 *                          <blinkofnight{doggy,bark-bark}gmail.com>       *
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/


#ifndef XYDATA_TEMPLATE_H
#define XYDATA_TEMPLATE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "qpoint.h"

#define XYDATA_MAX_ARRAY_SIZE 1048576000 //1000 Mbytes

/** If defined in Makefile anr somewhere else**/
#ifdef CEGUI
#include <CEGUI/Vector.h>
#endif

template <typename T>
class xydata
{

 public:

  /** \brief Construct class with empty pointers,user may call later one of these:
      set_data(int, T*); append(int, T*);
  */
  xydata();
  
  /** \brief Destructor will free private pointer to T (p),
      if not NULL.*/
  ~xydata();
  
  /**\brief Class contructor, will allocate arrays
     of size (param1), it will make a
     copy data from (param2) into inner Y array;
     X data values will be set to 0,1,2,3 ..
  */
  xydata(const size_t, const  T*);

  /**\brief Class contructor, will allocate inner arrays
     of size (param1) and will make:
     copy data from (param2) into inner X array.
     copy data from (param3) into inner Y array.*/
  xydata(const size_t,const  T*, const  T*);

  /** \brief Create class and copy values from pointer to
      another existing instance of the class.
      \param non-NULL pointer to xydata<T>. 
      Values will be simply copied.
  */
  xydata(const xydata<T> *other);

  /** \brief Create class and copy values from pointer to
      another existing instance of the class.

      \param reference of xydata<T>. 
      Values will be simply copied.
  */
  xydata(const xydata<T> &other);
  
  /** \brief allocate inner data arrays and copy values from
      std::vector<T> into Y-data array.
  */
  xydata(const std::vector <T>);

  /** \brief allocate inner data arrays and copy values from
      std::vector<T>.
      
     \param std::vector<T> data_x to be copied into inner x-data array;
      
     \param std::vector<T> data_y to be copied into inner Y-data array;
  */
  xydata(const std::vector <T>, const std::vector <T>);
  
  
  /**\brief Copy (param1) values of T from (param2) into inner array. */
  int set_data(const size_t, const T*);

  /**\brief Copy (param1) values of T
     from (param2) and  (param3) (mdata_curve_class) object*/
  int set_data(const size_t, const  T*, const  T*);

  /** \brief Copy data from link (xydata &) to object.*/
  int set_data(const xydata<T> &);
  
  /** Copy data from (xydata *).
      It will reallocate internal arrays, all will be fine.
      \param non-NULL pointer to xydata object.
      \return 0 on success, -1 is the given pointer got no data.
  */
  int set_data(const xydata<T> *);

  /** \brief Copy data from std vector to object.
      Y-values are set from data, X will be set to 0,1,2,3 ..*/
  int set_data(const std::vector <T> );
  
  /** \brief Copy data from std vectors to object.*/
  int set_data(const std::vector <T> , const std::vector <T>);
  

    
  /** \brief Copy inner data into other object of the same class.*/
  int copy_data(xydata<T> *) const;

  /** \brief Copy N values from inner data into other object of the same class.
      \param non-NULL pointer to other object.
      \param start index.
      \param end index.
   */
  int copy_nvalues(xydata<T> *result_xydata,
		   const size_t index_from, const size_t index_to) const;
  
  /** \brief Copy Y data into the given std::vector.
      If the given list is not empty -- it will call their clear() method.  */
  int copy_data(std::vector <T> &) const;
  
  /** \brief Copy XY data into the given std::vectors.
      If the given lists are not empty -- it will call their clear() method.
  */
  int copy_data(std::vector <T> &, std::vector <T> &) const;

  /** \brief Copy inner XY data into arrays of T values.
      \param counter: indicates how much was bytes copied.
      \param counter: indicates how much items bytes copied.
      \param target non-NULL pointer for X values.
      \param target non-NULL pointer for X values.
      \return 0 on success, -1 if empty or data pointer is NULL.
*/
  int copy_data(size_t &bcount, size_t &icount, T *xdata, T *ydata) const;
  
  /** \brief Copy inner X data into array of T values.
      \param counter: indicates how much was bytes copied.
      \param counter: indicates how much items bytes copied.
      \param target non-NULL pointer
      \return 0 on success, -1 if empty or data pointer is NULL.
*/
  int copy_xdata(size_t &bcount, size_t &icount, T *data) const;

  /** \brief Copy inner Y data into array of T values.
      \param counter: indicates how much was bytes copied.
      \param counter: indicates how much items bytes copied.
      \param target non-NULL pointer
      \return 0 on success, -1 if empty or data pointer is NULL.
  */
  int copy_ydata(size_t &bcount, size_t &icount, T *data) const;


  /** Take Y-values(ignoring all X[i]) and create a histogramm from them.
      It will count how much each Y value happens in the array
      and create histogramm with contents like:
        Y[i]  N_events
      
      \param reference to a bool value wo indicate whether it's ok.
      \return newly allocated xydata<T> pointer to class of bject. Return value may be NULL if operation failed.
      CALLER CARES ABOUT MEM. FREE.
   */
  xydata<T> *make_Y_histogramm(bool &success);

  /** Take X-values(ignoring Y[i]) and create a histogramm from them.
      It will count how much each Y value happens in the array
      and create histogramm with contents like:
        X[i]  N_events
      
      \param reference to a bool value wo indicate whether it's ok.
      \return newly allocated xydata<T> pointer to class ofbject.      CALLER CARES ABOUT MEM. FREE.
   */
  xydata<T> *make_X_histogramm(bool &success);

  /** Read array values from the file.
      \param filename.
      \param append
      whether to append to existing data:
      if true -- I append data to existing values(if there already are any),
      if false -- I use newly created inner arrays to keep values.
      \param max_read:
      maximum read values limitation.  if <=0 -- then no limit set.
      \return 0 if ok, -1 if file does not exist or it's unable for reading.
  */
  inline int read_file (const char* filename, bool append = false, int max_read = -1)
  {
    std::string name = filename;
    return this->read_file(name, append, max_read);
  }
  
  /** Write array values to the file.
      \param filename.
      \param append:
      whether to append data to file instead of rewriting it:
      if true -- I append text to file, if false -- I recreate given file.
      \param max_read:
      maximum write values limitation. if <=0 -- then no limit set.
  
      \return 0 if ok, -1 if file does not exist or it's unable for writing.
  */
  inline int write_file(const char* filename, bool append = false, size_t max_write = 0)
  {
    std::string name = filename;
    return this->write_file(name, append, max_write);
  }
  
  /** Read array values from the file.
      \param filename.
      \param append
      whether to append to existing data:
      if true -- I append data to existing values(if there already are any),
      if false -- I use newly created inner arrays to keep values.
      \param max_read:
      maximum read values limitation.  if <=0 -- then no limit set.
      \return 0 if ok, -1 if file does not exist or it's unable for reading.
  */
  int read_file (const std::string filename, bool append = false, size_t max_read = 0);
  
  /** Write array values to the file.
      \param filename.
      \param append:
      whether to append data to file instead of rewriting it:
      if true -- I append text to file, if false -- I recreate given file.
      \param max_read:
      maximum write values limitation. if <=0 -- then no limit set.
  
      \return 0 if ok, -1 if file does not exist or it's unable for writing.
  */
  int write_file(const std::string filename, bool append = false, size_t max_write = -1);
  
  /** \brief Set n_values=0, free pointer (p).*/
  int clear();

  /** \brief Return true if the inner array of data is empty.*/
  inline bool empty() const
  {
    return is_empty();
  }

  /** \brief Return true if the inner array of data is empty.*/
  inline bool isEmpty() const
  {
    return is_empty();
  }
    
  /** \brief Return true if the inner array of data is empty.*/
  bool is_empty() const;

  /** \brief print out array.*/
  int print() const;
  
  /** \brief Return number of values stored in array of T.*/
  size_t length() const;

  /** \brief Return number of values stored in array of T.*/
  size_t size() const;
  
  /** \brief Append new data to the one that already present.
      Will realloc inner array (p).
  */  
  int append(const size_t, const  T*);
  
  /** \brief Append new data to the one that already present.
      Will realloc inner array (p).
  */  
  int append(const size_t, const  T*, const  T*);
  
  /** \brief Set new array length.
      
      If new size is smaller than the previous values -- 
      it will just realloc with preserving data.
      If new size is greater -- it will fill new elements with 0.
      
      \return 0, always.
  */
  int change_length(const size_t);
  
  /** \brief Set new array length.
      
      If new size is smaller than the previous values -- 
      it will just realloc with preserving data.
      If new size is greater -- it will fill new elements with 0.
      \return 0 always.
  */
  int resize(const size_t);

  /** \brief set value of the i-th element of the array.*/
  int set_item_value(const size_t, const  T, const  T  );

  /** \brief set value of the i-th element of the array.*/
  int set_item_value(const size_t, const qpointf);  

  /** \brief set X value of the i-th element of the array.
      \param index inside array.
      \param new N-th x-value.
      \return 0 if index is in rage, -1 otherwise.
   */
  int setx(const size_t, const  T);

  /** \brief set Y value of the i-th element of the array.
      \param index inside array.
      \param new N-th y-value.
      \return 0 if index is in rage, -1 otherwise.
  */
  int sety(const size_t, const T);  
  
  /** \return values of the N-th element.*/
  qpointf at(const size_t, bool &success) const;

  /** \brief Get value of the N-th element into the pointer
      to array of 2 Ts.
      
      \param index: index at which we access the value.
      
      \param xy_value:  CALLER CARES! Valid non-NULL pointer
      to array of size >= 2 (2*sizeof(T) bytes)
      
      \return 0 if OK. -1 if pointer is NULL; -2 if index is out of bounds.
  */
  int at(const size_t index, T *xy_value) const;

#ifdef CEGUI
  /** \brief Get value of the N-th element into the pointer to array of 2 Ts.
      \param index
      index at which we access the value.
      \param a reference of CEGUI::Vector2<T>

      \return 0 if OK. -1 if pointer is NULL; -2 if index is out of bounds.
  */
  int at(const size_t index, CEGUI::Vector2<T> &cegui_vec2) const;
  
#endif

  /** \return Y-value of the N-th point.*/
  T y(const size_t, bool &success) const;

  /** \return Y-value of the N-th point.*/
  T x(const size_t, bool &success) const;
  
  /** \return Y-value of the N-th point.*/
  T y_at(const size_t, bool &success) const;

  /** \return Y-value of the N-th point.*/
  T x_at(const size_t, bool &success) const;
  
  /** \brief Find Y value for it's X. */
  T y_at_x(bool &success, const T xval, const T numerror) const;
  

  /** \brief Find X value for it's Y. */
  T x_at_y(bool &success, const T xval, const T numerror) const;
  
  /** \brief get minimum value from X data array*/
  T get_min_x(bool &success);
  
  /** \brief get minimum value from Y data array*/
  T get_min_y(bool &success);
  
  /** \brief get maximum value from X data array*/
  T get_max_x(bool &success);

  /** \brief get index of maximum value from Y data array*/
  T get_max_y(bool &success);
  
  /** \brief get maximum Y value at given X-region.
      \param Lesser X-region value.
      \param Bigger Y-region value.
      \return T value: max. Y.
  */
  T max_y_local(const T x1, const T x2, bool &success);
  
  
  /** \brief get maximum X value at given region of Y-values..
      \param Lesser Y-region value.
      \param Bigger Y-region value.
      \return T value: max. Y.
  */
  T max_x_local(const T y1, const T y2, bool &success);

  /** \brief get maximum Y value at given X-region.
      \param Lesser X-region value.
      \param Bigger X-region value.
      \return T value: min. Y.
  */
  T min_y_local(const T x1, const T x2, bool &success);

  /** \brief get min X value at given Y-region.
      \param Lesser Y-region value.
      \param Bigger Y-region value.
      \return T value: min. X.
  */
  T min_x_local(const T y1, const T y2, bool &success);

  
  /** \brief get index of minimum value from X data array*/
  size_t get_index_min_x();
  
  /** \brief get index of minimum value from Y data array*/
  size_t  get_index_min_y();
  
  /** \brief get index of maximum value from X data array*/
  size_t  get_index_max_x();

  /** \brief get index of maximum value from Y data array*/
  size_t  get_index_max_y();
  
  /** \brief get average value from Y data array
      \param indicator whether value has been calculated,
      if false, then the arrays are empty.
   */
  T average_y(bool &ok);

  /** \brief get average value from X data array
      \param indicator whether value has been calculated,
      if false, then the arrays are empty.
  */
  T average_x(bool &ok);

  /** \brief get standart deviation from Y data array.
      Formula used: sigma = sqrt(1/(N-1) * Sum((averageY - Y[i])^2))
      \param indicator whether value has been calculated,
      if false, then the arrays are empty.
  */
  T SDY(bool &ok);

  /** \brief get standart deviation of the mean value from Y data array.
      Formula used: sigma = sqrt(1/(N-1)/N * Sum((averageY - Y[i])^2))
      \param indicator whether value has been calculated,
      if false, then the arrays are empty.
  */
  T SDMEAN_Y(bool &ok);

  /** \brief get standart deviation of the mean value from X data array.
      Formula used: sigma = sqrt(1/(N-1)/N * Sum((averageX - X[i])^2))
      \param indicator whether value has been calculated,
      if false, then the arrays are empty.
  */
  T SDMEAN_X(bool &ok);

  /** \brief get standart deviation from Y data array.
      Formula used: sigma = sqrt(1/(N-1) * Sum((averageX - X[i])^2))
      \param indicator whether value has been calculated,
      if false, then the arrays are empty.
  */
  T SDX(bool &ok);

  /** \brief sum of Y values;
      \param indicator whether value has been calculated,
      if false, then the arrays are empty.
  */
  T SUMY(bool &ok);

  /** \brief sum of X values;
      \param indicator whether value has been calculated,
      if false, then the arrays are empty.
  */
  T SUMX(bool &ok);
    
  /** \brief Find index of nearest point to the given coordinates.
      Returns (-1) on fail or integer in range [0,n_values-1] on success.
  */
  size_t find_index(const T x, const T y, bool &success);
  
  /** \brief Find index of nearest point to the given coordinates.
      \param X-value which caller may want to find in the array. 
      \return Returns (-1) on fail or integer in range [0,n_values-1] on success.
  */
  size_t find_index_x(const T x, bool &success);
  
  /** \brief Find index of nearest point to the given coordinates.
      \param Y-value which caller may want to find in the array.
      \return Returns (-1) on fail or integer in range [0,n_values-1] on success.
  */
  size_t find_index_y(const T y, bool &success);
  
  /** \brief Find index of nearest point to the given coordinates.
      Returns (-1) on fail or integer in range [0,n_values-1] on success.
  */
  size_t find_index(const qpointf point, bool &success);

  /** Exchange values of X and Y:
      it will make internal X-data array to be equal to Y values,
      Y values to be equal to previous X values.
  */
  void swap_xy();
  
  /** Revert order in both arrays. 
      This will change internal arrays, but their size will stay the same.
      If you dont want a change, then make a copy of this xydata<T> class object.*/
  void revert_values_order();
  
  /** Sort 2 internal arrays by X values in increasing orders.
      This will change internal arrays, but their size will stay the same.
      If you dont want a change, then make a copy of this xydata<T> class object.*/
  void sort_ascending_x();
  
  /** Sort 2 internal arrays by Y values in increasing orders.
      This will change internal arrays, but their size will stay the same.
      If you dont want a change, then make a copy of this xydata<T> class object.*/
  void sort_ascending_y();

  /** Sort 2 internal arrays by X values in increasing orders.
      This will change internal arrays, but their size will stay the same.
      If you dont want a change, then make a copy of this xydata<T> class object.
  */
  void sort_descending_x();
  
  /** Sort 2 internal arrays by Y values in increasing orders.
      This will change internal arrays, but their size will stay the same.
      If you dont want a change, then make a copy of this xydata<T> class object.*/
  void sort_descending_y();
    
  /** Return a pointer to internal buffer with X-data.
      \param reference of a variable to keep size of the pointer in bytes.
      \param reference of a variable to keep quantity of items in array pointed by pointer.
   */
  inline const T* get_xpointer(size_t &bytes_count, size_t &items_count);
  

  /** Return a pointer to internal buffer with X-data.
      \param reference of a variable to keep size of the pointer in bytes.
      \param reference of a variable to keep quantity of items in array pointed by pointer.
   */
  inline const T* get_ypointer(size_t &bytes_count, size_t &items_count);
  
 protected:
  
  /** pointer to array of T.*/
  T *px;
  
  /** pointer to array of T.*/
  T *py;
  
  /** py and px arrays length. */
  size_t  n_values;
  
  /** True if we're not using auto-filled with 0,1,2,3 X-array.*/
  bool user_x_values;
  
  /** When writing new functions like
      set_data(...) or append(...), set this variable to (true),
      if data setting  was successfull.
      Many other functions here rely on it.
  */
  bool p_is_null;
  
 private:
  /** indicates that something has changed data.*/
  bool modified;
  
  T stored_xmin;
  T stored_xmax;
  T stored_ymin;
  T stored_ymax;
  
  /** Private function which checks the value of
      int n_values
      reallocates the px, py arrays. Makes malloc(..) if they were NULL.
    
      Only used internally to shorten code, just in few cases!
  */
  void check_and_realloc_py_px()
  {
    if(n_values > 0)
      {
	if(!is_empty())
	  {
	    px = (T*)realloc((void*)px, sizeof(T)*(n_values));
	    py = (T*)realloc((void*)py, sizeof(T)*(n_values));
	  }
	else
	  {
	    px = (T*)malloc(sizeof(T)*(n_values));
	    py = (T*)malloc(sizeof(T)*(n_values));	  
	  }
      }
  }
  
  /** used in constructors only.*/
  void construct()
  {
    modified = true;
    px = NULL;
    py = NULL;
    user_x_values = false;
    n_values  = 0;
    p_is_null = true;
  }

  /** \brief
      Recalculate all XY min/max values and store them.
      Don't worry, it runs only one loop to do that.
  */
  inline void recalc_min_max()
  {
    if( is_empty()) return;
  
    stored_xmin=px[0]; stored_xmax=px[0];
    stored_ymin=py[0]; stored_ymax=py[0];
    T tmp=0;
    for(size_t i=1; i<n_values; i++)
      {
	tmp = px[i];
	if(stored_xmin > tmp) stored_xmin = tmp;
	if(stored_xmax < tmp) stored_xmax = tmp;
      
	tmp = py[i];
	if(stored_ymin > tmp) stored_ymin = tmp;
	if(stored_ymax < tmp) stored_ymax = tmp;
      }
    modified = false;
  }

};//end of class



template <typename T>
xydata<T>::xydata()
{
  construct();
}

/** Class constructor: copy Y data from arrays by given pointers
    into internal arrays. X data will be filled with 0,1,2,3 .. values.
*/
template <typename T>
xydata<T>::xydata(const size_t N, const T *data)
{
  construct();
  set_data(N, data);
}



/** \brief Create class and copy values from pointer to
    another existing instance of the class.
    Values will be simply copied.
**/
template <typename T>
xydata<T>::xydata(const xydata<T> *other)
{
  construct();
  set_data(other);
}

template <typename T>
xydata<T>::xydata(const xydata<T> &other)
{
  construct();
  set_data(other);
}

/** \brief allocate inner data arrays and copy values from
    std::vector<T> into Y-data array.
*/
template <typename T>
inline xydata<T>::xydata(std::vector <T> data)
{
  construct();
  set_data(data);
}


template <typename T>
inline xydata<T>::xydata(std::vector <T> data_x, std::vector <T> data_y)
{
  construct();
  set_data(data_x, data_y);
}

/** Class constructor: copy XY data from arrays by given pointers
    into internal arrays(allocates memory inside)*/
template <typename T>
inline xydata<T>::xydata(const size_t N,
			 const T *data_x, const T *data_y)
{
  construct();
  
  if( (N>0) && (data_y!=NULL))
    {
      py = (T*)malloc(sizeof(T)*N);
      px = (T*)malloc(sizeof(T)*N);
      memmove((void*)px, (void*)data_x, N*sizeof(T));      
      memmove((void*)py, (void*)data_y, N*sizeof(T));
      user_x_values = true;      
      p_is_null = false;
      n_values = N;
    }
}

template <typename T>
inline xydata<T>::~xydata()
{
  if(!is_empty())
    {
      free(py);
      free(px);
    }
}

/**  
     \return value of item number (param).
     Returns qpointf(0,0) if given index is out of bounds.
*/
template <typename T>
inline qpointf  xydata<T>::at(const size_t i, bool &success) const
{
  qpointf point(0,0);
  if( i > n_values)
    {
      success = false;
      return point;
    }
  if( !is_empty())
    {
      point =  qpointf((qreal)px[i],(qreal)py[i]);
      success = true;
      return point;
    }
  success = false;
  return point;
}

/** \brief Get value of the N-th element into the pointer to array of 2 Ts.
    \param xy_value
    CALLER CARES!
    Valid non-NULL pointer to array of size >= 2 (2*sizeof(T) bytes)
    \return 0 if OK. -1 if pointer is NULL; -2 if index is out of bounds.
*/
template <typename T>
inline int xydata<T>::at(const size_t index, T *xy_value) const
{
  if(xy_value == NULL) return -1;
  if(index < n_values && !is_empty())
    {
      xy_value[0] = px[index];
      xy_value[1] = py[index];
      return 0;
    }
  return -2;
}

#ifdef CEGUI
/** \brief Get value of the N-th element into the pointer to array of 2 Ts.
    \param index
    index at which we access the value.
    \param a reference of CEGUI::Vector2<T>

    \return 0 if OK. -1 if pointer is NULL; -2 if index is out of bounds.
*/
template <typename T>
inline int xydata<T>::at(const size_t index, CEGUI::Vector2<T> &cegui_vec2) const
{
  if(index < n_values && !is_empty())
    {
      cegui_vec2 = CEGUI::Vector2<T>(px[index],py[index]);
      return 0;
    }
  return -2;

}
#endif

/** \return Y-value of the N-th point.*/
template <typename T>
inline T xydata<T>::y_at(const size_t i, bool &success) const
{
  if(i > n_values)
    {
      success = false;
      return -1;
    }

  if(!is_empty())
    {
      success = true;
      return py[i];
    }
  success = false;
  return 0;
}

/** \return X-value of the N-th point.*/
template <typename T>
inline T xydata<T>::x_at(const size_t i, bool &success) const
{
  if(i> n_values)
    {
      success = false;
      return -1;
    }

  if(!is_empty())
    {
      success = true;
      return px[i];
    }
  success = false;
  return 0;
}

/** \return X-value of the N-th point.*/
template <typename T>
T xydata<T>::x(const size_t i, bool &success) const
{
  return x_at(i, success);
}

template <typename T>
T xydata<T>::y(const size_t i, bool &success) const
{
  return y_at(i, success);
}

/** \brief Find Y value for it's X. */
template <typename T>
inline T xydata<T>::y_at_x(bool &success, const T xval, const T numerror=1e-16 ) const
{

  if( !is_empty() )
    {
      size_t k = 0;
      while( k < n_values)
	{
	  if(qFuzzyIsNull(qAbs( px[k] - xval)))
	    {
	      success = true;
	      return py[k];
	    }
	  k++;
	}
      success = false;
    }
  success = false;
  return 0;
}

/** \brief Find X value for it's Y. */
template <typename T>
inline T xydata<T>::x_at_y(bool &success, const T xval, const T numerror=1e-16 ) const
{
  if( !is_empty())
    {
      size_t k=0;
      while(k<n_values)
	{
	  if(qFuzzyIsNull(qAbs(py[k] - xval)))
	    {
	      success = true;
	      return px[k];
	    }
	  k++;
	}
      success = false;
    }
  success = false;
  return -1;
}

/** \brief Return number of values stored in array of T.*/
template <typename T>
size_t xydata<T>::length() const
{
  return n_values;
}

template <typename T>
size_t xydata<T>::size() const
{
  return n_values;
}

/** append data from (param2) to Y-values, refill X values with 0,1,2,3 ..
    Function makes copy of the buffer given by(param2),
    caller may delete[but only outside the scope of this method, of course]
    pointer at (param2) after usage. */
template <typename T>
inline int xydata<T>::append(const size_t N_append, const T *data)
{
  if( (N_append > 0) && (data!=NULL))
    {
      if(!is_empty())
	{//preserve old data and append new one:
	  px = (T*)realloc((void*)px, sizeof(T)*(n_values+N_append));
	  for(int i=n_values; i<(n_values+N_append); i++)  px[i] = i+px[n_values-1];
	  
	  py = (T*)realloc((void*)py, sizeof(T)*(n_values+N_append));
	  //now go to the end of previous data:
	  //and copy data to there:
	  memmove((void*)(py + n_values), (void*)data, N_append*sizeof(T));
	  
	  //set counter of how much values there:
	  n_values += N_append;
	}
      else 
	{
	  this->set_data(N_append, data);
	}
      
      p_is_null = false;
      modified = true;
      return 0;
    }
  return -1;
}

/** append data from (param2) to X-values, append data from (param3)
    to Y-values.
    Function makes copy of the buffers given by(param2, param3),
    caller may delete [but only outside the scope of this method, of course]
    pointers at (param2, param3) after usage. 
*/
template <typename T>
inline int xydata<T>::append(const size_t N_append,
			     const T *data_x, const T *data_y)
{
  if(data_y ==NULL) return -1;
  
  //usual case:
  if(!is_empty())
    {
      //preserve old Y data and append new one:
      py = (T*)realloc((void*)py, sizeof(T)*(n_values+N_append));
      //now go to the end of previous data:
      T *p_shifted = py + n_values;
      //and copy data to there:
      memmove((void*)p_shifted, (void*)data_y, N_append*sizeof(T));

      //preserve old X data and append new one:
      px = (T*)realloc((void*)px, sizeof(T)*(n_values+N_append));
      //now go to the end of previous data:
      p_shifted = (px + n_values);
      //and copy data to there:
      memmove((void*)p_shifted, (void*)data_x, N_append*sizeof(T));
      //set counter of how much values there:
      n_values += N_append;
      
      p_is_null = false;
      modified = true;
      return 0;
    }
  else
    {//else, if we were empty:
      return set_data(N_append, data_x, data_y);
    }
  return -1;
}


/**
   Copy (param1) values of T from (param2) into inner array.
   X array will be allocated and filled with 0,1,2,3 ...
   Function makes copy of the buffers given by(param2),
   caller may delete [but only outside the scope of this method]
   pointer at (param2) after usage.*/
template <typename T>
inline int xydata<T>::set_data(const size_t N, const T *data)
{
  if( (N>0) && (data!=NULL))
    {
      n_values = N;
      check_and_realloc_py_px();
      for(size_t i = 0; i < n_values; i++)
	px[i] = i;
      //copy:
      memmove((void*)py, (void*)data, n_values*sizeof(T));
      p_is_null = false;
      modified = true;
      return 0;
    }
  else
    {
#ifdef DEBUG
      std::cout << "int xydata<T>::set_data(const int N, const T *data): Invalid number of elements or NULL pointer given!";
#endif
    }
  return -1;
}

/** Copy (param1) values of T
    from (param2) into inner X array;
    from (param3) into inner Y array;
     
    Function makes copy of the buffers given by(param2,param3),
    caller may delete [but only outside the scope of this method]
    pointer at (param2,param3) after usage.
*/
template <typename T>
inline int xydata<T>::set_data(const size_t N,
			       const T *data_x, const T *data_y)
{
  if( (N > 0) && (data_y!=NULL) && (data_y!=NULL))
    {
      this->n_values = N;
      check_and_realloc_py_px();
      //copy x:
      memmove((void*)px, (void*)data_x, n_values*sizeof(T));
      //copy y:
      memmove((void*)py, (void*)data_y, n_values*sizeof(T));
      p_is_null = false;
      modified  = true;
      return 0;
    }
#ifdef DEBUG
  else
    {
      std::cout << "int xydata<T>::set_data(const int N, const T *data): Invalid number of elements or NULL pointer given!";
    }
#endif
  return -1;
}

/** Copy data from (xydata<T> *).
    It will reallocate internal arrays, all will be fine.
    
    \return 0 on success, -1 is the given pointer got no data.
*/
template <typename T>
inline int xydata<T>::set_data(const xydata<T> *data)
{
  if(data!=NULL)
    {
      std::vector <T> listx,listy;
      data->copy_data(listx,listy);
      int res = this->set_data(listx, listy);
      if(!listx.empty()) listx.clear();
      if(!listy.empty()) listy.clear();
      return res;
    }
  return -1;
}

/** Copy data from link (xydata<T>)  object.
    It will reallocate internal arrays, all will be fine.
    
    \return 0 on success
*/
template <typename T>
inline int xydata<T>::set_data(const xydata<T> &data)
{
  std::vector <T> listx,listy;
  data.copy_data(listx,listy);
  int res = this->set_data(listx, listy);
  if(!listx.empty()) listx.clear();
  if(!listy.empty()) listy.clear();
  return res;
}


/** A function to copy data from std::vector <T>.
    Y values are set from list given in (param2).
    X values will be set to 0,1,2,3...
    It will reallocate internal arrays, all will be fine.
    
    \return 0 on success, -1 is the given list got no data.
*/
template <typename T>
inline int xydata<T>::set_data(const std::vector <T> list)
{
  size_t N = list.size();
  if( N > 0 )
    {
      n_values = N;
      check_and_realloc_py_px();
      //copy:
      for(size_t i=0; i < n_values; i++)
	{
	  px[i] = (T)i;
	  py[i] = (T)list.at(i);
	}
      p_is_null = false;
      modified  = true;
      return 0;
    }
  else
    {
#ifdef DEBUG
      std::cout << "int xydata<T>::set_data(QList <T>  list): Invalid number of elements!";
#endif
    }
  return -1;
}


#ifdef D_USING_QT4
/** A function to copy data from:
    QList if Qt4 is used;
    (a) from std::vector <T> in all other cases;

    X values are set from list given in (param1).
    Y values are set from list given in (param2).
    It will reallocate internal arrays, all will be fine.
    
    \return 0 on success, -1 is the given list got no data.
*/
template <typename T>
inline int xydata<T>::set_data(const QList <T> list_x,
			       const QList <T> list_y)

{
  size_t N = 0;
  //if list sizes are not equal then we choose minimal value:
  N = (list_x.size() < list_y.size())? list_x.size() : list_y.size();
  
  //now realloc and copy data:
  if( N > 0 )
    {
      n_values = N;
      check_and_realloc_py_px();
      //copy:
      for(size_t i=0; i < n_values; i++)
	{
	  px[i] = list_x.at(i);
	  py[i] = list_y.at(i);
	}
      p_is_null = false;
      modified  = true;      
      return 0;
    }
#ifdef DEBUG
  else
    {
      std::cout << "int xydata<T>::set_data(QList <T> , QList <T> ): Invalid number of elements!";
    }
#endif
  return -1;
}
#endif

/** A function to copy data
    from std::vector <T> in all other cases;

    X values are set from list given in (param1).
    Y values are set from list given in (param2).
    It will reallocate internal arrays, all will be fine.
    
    \return 0 on success, -1 is the given list got no data.
*/
template <typename T>
inline int xydata<T>::set_data(const std::vector <T> list_x,
			       const std::vector <T> list_y)
{
 size_t N = 0;
  //if list sizes are not equal then we choose minimal value:
 N = qMin(list_x.size(), list_y.size());
  
  //now realloc and copy data:
  if( N > 0 )
    {
      n_values = N;
      check_and_realloc_py_px();
      //copy:
      for(size_t i = 0; i < n_values; i++)
	{
	  px[i] = list_x.at(i);
	  py[i] = list_y.at(i);
	}
      p_is_null = false;
      modified  = true;
      return 0;
    }
#ifdef DEBUG
  else
    {
      std::cout << "int xydata<T>::set_data(QList <T> , QList <T> ): Invalid number of elements!";
    }
#endif
  return -1;
}

/** Reallocates these (protected) pointers to T: T *px, *py
    So that they will have new length of (param1).
    Old Y values preserved, newly added values set to 0.
    Old X values preserved, newly added values set to 0.
    If new array's length is smaller than it's previous value,
    then no values changed except arrays's length.

    \return 0 if given param1 is OK, -1 otherwise.
*/
template <typename T>
inline int xydata<T>::resize(const size_t N_new_len)
{
  return change_length(N_new_len);
}

/** Reallocates these (protected) pointers to T: T *px, *py
    So that they will have new length of (param1).
    Old Y values preserved, newly added values set to 0.
    Old X values preserved, newly added values set to 0.
    If new array's length is smaller than it's previous value,
    then no values changed except arrays's length.

    \return 0 if given param1 is OK, -1 otherwise.
*/
template <typename T>
inline int xydata<T>::change_length(const size_t N_new_len)
{
  if( N_new_len == n_values ) return 0;
  if(N_new_len < 1) {clear(); return 0;}
  if(N_new_len < n_values && N_new_len > 1)
    {
      T *nx = (T*)malloc(sizeof(T)*N_new_len);
      T *ny = (T*)malloc(sizeof(T)*N_new_len);
      memset((void*)nx, 0x00, (size_t)(sizeof(T)*N_new_len));
      memset((void*)ny, 0x00, (size_t)(sizeof(T)*N_new_len));
      if( !is_empty())
	{
	  memmove((void*)nx, (void*)px, (size_t) (N_new_len*sizeof(T)));
	  memmove((void*)ny, (void*)py, (size_t) (N_new_len*sizeof(T)));
	  free(px);
	  free(py);
	}
      px = nx;
      py = ny;
      n_values = N_new_len;
      modified = true;
      return 0;
    }
  else
  if( N_new_len > n_values && N_new_len > 1)
    {
      int previous_n_values = n_values;
      n_values = N_new_len;
      
      int start_pos=0;
      if(N_new_len > previous_n_values) start_pos = previous_n_values-1;
      
      //allocate and fill new bytes with 0 if needed
      if(py!=NULL)
	{
	  py = (T*)realloc((void*)py, sizeof(T)*n_values);
	  memset((void*)(py+start_pos), 0x00, sizeof(T)*(n_values-start_pos));
	}
      else
	{
	  py = (T*)malloc(sizeof(T)*n_values);
	  memset((void*)py, 0x00, sizeof(T)*(n_values));
	}
      
      if(px!=NULL)
	{
	  px = (T*)realloc((void*)px, sizeof(T)*n_values);
	  memset((void*)(px+start_pos), 0x00, sizeof(T)*(n_values-start_pos));
	}
      else
	{
	  px = (T*)malloc(sizeof(T)*n_values);
	  memset((void*)px, 0x00, sizeof(T)*(n_values));
	}
      
      p_is_null = false;
      modified = true;      
      return 0;
    }
  return 0;
}

/** set X value of the i-th element of the array.
    param1: index inside array.
    param2: new N-th x-value.
**/
template <typename T>
int xydata<T>::setx(const size_t index, const  T value)
{
  if(!is_empty() && index < n_values)
    px[index] = value;
  else return -1;
  return 0;
}

/** \brief set Y value of the i-th element of the array.
    param1 index inside array.
    param2: new N-th y-value.
**/
template <typename T>
int xydata<T>::sety(const size_t index, const  T value)
{
  if(!is_empty() && index < n_values)
    py[index] = value;
  else return -1;
  return 0;
}

/** Check whether internal buffers are OK and
    set (X,Y) value of the i-th element.
    X[i]=(param1);     Y[i]=(param2);
    
    \return 0 if given i-number is inside the array bounds, -1 otherwise.
*/
template <typename T>
inline int xydata<T>::set_item_value(const size_t i,
				     const T value_x,
				     const T value_y)
{
  
  if( is_empty()) 
    {
#ifdef DEBUG
      std::cout << "int xydata<T>::set_item_value(const size_t i,\
const T value_x, const T value_y): Arrays are empty NULLs!\n";
#endif
      return -1;
    }
  
  if( (0<=i) && (i<n_values))
    {
      px[i] = value_x;
      py[i] = value_y;
    }
  else
    {
#ifdef DEBUG
      std::cout << "int xydata<T>::set_item_value(const size_t i,\
const T value_x, const T value_y): Out of bounds!\n";
#endif
      return -1;
    }
  modified = true;  
  return 0;
}


/** Check whether internal buffers are OK and
    set (X,Y) value of the i-th element.
    X[i]=point.x();     Y[i]=point.x();
    
    \return 0 if given i-number is inside the array bounds,
    -1 otherwise. Also returns -1 if values have not been set
    (and thus, internal arrays are not allocated).
*/
template <typename T>
inline int xydata<T>::set_item_value(const size_t i, const qpointf point)
{
  
  if( is_empty()) 
    {
#ifdef DEBUG
      std::cout << "int xydata<T>::set_item_value(const size_t i,\
const T value_x, const T value_y): Arrays are empty NULLs!\n";
#endif
      return -1;
    }
  
  if( (0<=i) && (i<n_values))
    {
      px[i] = point.x();
      py[i] = point.y();
    }
  else
    {
#ifdef DEBUG
      std::cout << "int xydata<T>::set_item_value(const size_t i,\
const T value_x, const T value_y): Out of bounds!\n";	  
#endif
      return -1;
    }
  
  return 0;
}

/** \return minimum value from the X-array.
    WARNING! -1 returned if no data has been set yet.
*/
template <typename T>
inline T xydata<T>::get_min_x(bool &success)
{
  if( is_empty()) 
    {
#ifdef DEBUG
      std::cout << "T xydata<T>::get_min_x(): Arrays are empty NULLs!\n";
#endif
      success = false;
      return -1;
    }
  success = true;
  if(!modified) return stored_xmin;
  recalc_min_max();
  return stored_xmin;
}

/** \return minimum value from the Y-array.
    WARNING! -1 returned if no data has been set yet.
*/
template <typename T>
inline T xydata<T>::get_min_y(bool &success)
{
  if(is_empty()) 
    {
#ifdef DEBUG
      std::cout << "T xydata<T>::get_min_y(): Arrays are empty NULLs!\n";
#endif
      success = false;
      return -1;
    }
  success = true;
  if(!modified) return stored_ymin;
  recalc_min_max();
  return stored_ymin;
}

/** \return max value from the X-array.
    WARNING! -1 returned if no data has been set yet.
*/
template <typename T>
inline T xydata<T>::get_max_x(bool &success)
{
  if( is_empty()) 
    {
#ifdef DEBUG
      std::cout << "T xydata<T>::get_min_y(): Arrays are empty NULLs!\n";
#endif
      success = false;
      return -1;
    }
  success = true;
  if(!modified) return stored_xmax;
  recalc_min_max();
  return stored_xmax;
}

/** \return max value from the Y-array.
    WARNING! -1 returned if no data has been set yet.
*/
template <typename T>
inline T xydata<T>::get_max_y(bool &success)
{
  if( is_empty()) 
    {
#ifdef DEBUG
      std::cout << "T xydata<T>::get_min_y(): Arrays are empty NULLs!\n";
#endif
      success = false;
      return -1;
    }
  success = true;
  if(!modified) return stored_ymax;
  recalc_min_max();
  return stored_ymax;
}

/** \brief get maximum Y value at given X-region.
    \param Lesser X-region value.
    \param Bigger X-region value.
    \return T value: max. Y.
*/
template <typename T>
inline T xydata<T>::max_y_local(const T x1, const T x2, bool &success)
{
  if(this->is_empty())
    {
      success = false;
      return -1;
    }
  size_t xi1 = find_index_x(x1);
  size_t xi2 = find_index_x(x2);
  if( (xi2<xi1)||(xi1 < 0)) 
    {
      success = false;
      return -1;
    }
  T max = py[xi1];
  for(size_t i=xi1; i<xi2; i++)
    {
      if(max < py[i]) max = py[i] ;
    }
  success = true;
  return max;
}

/** \brief get maximum X value at given Y-region.
    \param Lesser Y-region value.
    \param Bigger Y-region value.
    \return T value: max. Y.
*/
template <typename T>
inline T xydata<T>::max_x_local(const T y1, const T y2, bool &success)
{
  if(this->is_empty())
    {
      success = false;
      return -1;
    }
  int yi1 = find_index_y(y1);
  int yi2 = find_index_y(y2);
  if( (yi2<yi1)||(yi1 < 0)) 
    {
      success = false;
      return -1;
    }
  T max = px[yi1];
  for(int i=yi1; i<yi2; i++)
    {
      if(max < px[i]) max = px[i] ;
    }
  success = true;
  return max;
}

/** \brief get maximum Y value at given X-region.
    \param Lesser X-region value.
    \param Bigger X-region value.
    \return T value: min. Y.
*/
template <typename T>
inline T xydata<T>::min_y_local(const T x1, const T x2, bool &success)
{
  if(this->is_empty())
    {
      success = false;
      return -1;
    }
  int xi1 = find_index_x(x1);
  int xi2 = find_index_x(x2);
  if( (xi2<xi1)||(xi1 < 0)) 
    {
      success = false;
      return -1;
    }
  T min = py[xi1];
  for(int i=xi1; i<xi2; i++)
    {
      if(min > py[i]) min = py[i] ;
    }
  success = true;
  return min;
}

/** \brief get min X value at given Y-region.
    \param Lesser Y-region value.
    \param Bigger Y-region value.
    \return T value: min. X.
*/
template <typename T>
inline T xydata<T>::min_x_local(const T y1, const T y2, bool &success)
{
  if(this->is_empty())
    {
      success = false;
      return -1;
    }
  int yi1 = find_index_y(y1);
  int yi2 = find_index_y(y2);
  if( (yi2<yi1)||(yi1 < 0)) 
    {
      success = false;
      return -1;
    }
  T min = px[yi1];
  for(int i=yi1; i<yi2; i++)
    {
      if(min > px[i]) min = px[i] ;
    }
  success = true;
  return min;
}


/** \return index of minimum value from X data array
    WARNING! -1 returned if no data has been set yet.
*/
template <typename T>
inline size_t xydata<T>::get_index_min_x()
{
  if( is_empty()) 
    {
#ifdef DEBUG
      std::cout << "T xydata<T>::get_index_min_y(): Arrays are empty NULLs!\n";
#endif
      return -1;
    }
  
  size_t index = 0;
  T min = px[0];
  for(size_t i=1; i < n_values; i++)
    {
      if(min > px[i])
	{
	  index = i ;
	  min = px[i];
	}
    }
  return index;
}

/** \return index of minimum value from Y data array
    WARNING! -1 returned if no data has been set yet.
*/
template <typename T>
inline size_t xydata<T>::get_index_min_y()
{
  if( is_empty()) 
    {
#ifdef DEBUG
      std::cout << "T xydata<T>::get_index_min_y(): Arrays are empty NULLs!\n";
#endif
      return -1;
    }
  
  size_t index = 0;
  T min = py[0];
  for(size_t i = 1; i < n_values; i++)
    {
      if(min > py[i])
	{
	  min = py[i];
	  index = i;
	}
    }
  return index;
}

/** \return index of maximum value from X data array
    WARNING! -1 returned if no data has been set yet.
*/  
template <typename T>
inline size_t xydata<T>::get_index_max_x()
{
  if( is_empty()) 
    {
#ifdef DEBUG
      std::cout << "T xydata<T>::get_index_min_y(): Arrays are empty NULLs!\n";
#endif
      return -1;
    }
  
  size_t index = 0;
  T max = px[0];
  for(size_t i=1; i<n_values; i++)
    {
      if(max < px[i])
	{
	  max = px[i];
	  index = i;
	}
    }
  return index;
}

/** \return index of maximum value from Y data array
    WARNING! -1 returned if no data has been set yet.
*/
template <typename T>
inline size_t xydata<T>::get_index_max_y()
{
  if( is_empty()) 
    {
#ifdef DEBUG
      std::cout << "T xydata<T>::get_index_min_y(): Arrays are empty NULLs!\n";
#endif
      return -1;
    }
  
  size_t index = 0;
  T max = py[0];
  for(size_t i=1; i<n_values; i++)
    {
      if(max < py[i])
	{
	  max = py[i];
	  index = i;
	}
    }
  return index;
}

/** Find index of nearest point to the given coordinates.
    \return -1 on fail or integer [0, n_values-1] on success.
*/
template <typename T>
inline size_t xydata<T>::find_index(const qpointf point, bool &success)
{
  return find_index(point.x(), point.y(), success);
}

/** Find index of nearest point to the given coordinates.
    \return -1 on fail or integer [0, n_values-1] on success.
*/
template <typename T>
inline size_t xydata<T>::find_index(const T x, const T y, bool &success)
{
  success = false;
  if(is_empty()) return -1;
  
  for(size_t i=0; i<n_values; i++)
    {
      success = (qFuzzyIsCompare(px[i],x) && qFuzzyIsCompare(py[i],y));
      if( success) return i;
    }
  
  return 0;
}

/** Find index of nearest point to the given coordinates.
    \return -1 on fail or integer [0, n_values-1] on success.
*/
template <typename T>
inline size_t xydata<T>::find_index_x(const T x, bool &success)
{
  success = false;
  if(is_empty()) return -1;
  
  for(size_t i=0; i<n_values; i++)
    {
      success = qFuzzyIsCompare(px[i],x);
      if( success) return i;
    }
  return 0;
}

/** Find index of nearest point to the given coordinates.
    \return -1 on fail or integer [0, n_values-1] on success.
*/
template <typename T>
inline size_t xydata<T>::find_index_y(const T y, bool &success)
{
  success = false;
  if(is_empty()) return -1;
  
  for(size_t i=0; i<n_values; i++)
    {
      success = qFuzzyIsCompare(py[i],y);
      if( success) return i;
    }
  return 0;
}

/** get average value from Y data array.
    \return a value..
**/
template <typename T>
inline T xydata<T>::average_y(bool &ok)
{
  ok = false;
  if(is_empty())
    {
      return -1.0;
    }
  T sum = (T)0;
  for(size_t i=0; i < n_values; i++)  sum += py[i];
  ok = true;
  return sum/n_values;
}

/** get average value from X data array.
    \return a value..
**/
template <typename T>
inline T xydata<T>::average_x(bool &ok)
{
  ok = false;
  if(is_empty())
    {
      return -1.0;
    }
  T sum = (T)0;
  for(size_t  i=0; i < n_values; i++)  sum += px[i];
  ok = true;
  return sum/n_values;
}

/** Standart deviation.
**/
template <typename T>
inline T xydata<T>::SDY(bool &ok)
{
  ok = false;
  if(is_empty())
    {
      return -1.0;
    }
  ok = true;
  if(n_values == 1) return 0;
  T av = average_y(ok);
  T sum = (T)0;
  for(size_t i=0; i < n_values; i++)
    sum += pow(py[i] - av, 2.0);
  
  return sqrt(sum/(n_values - 1));
}

template <typename T>
inline T xydata<T>::SDX(bool &ok)
{
  ok = false;
  if(is_empty())
    {
      return -1.0;
    }
  ok = true;
  if(n_values == 1) return 0;
  T av = average_x(ok);
  T sum = (T)0;
  for(size_t i=0; i < n_values; i++)
    sum += pow(px[i] - av, 2.0);

  return sqrt(sum/(n_values - 1));
}

/** \brief get standart deviation of the mean value from Y data array.
    Formula used: sigma = sqrt(1/(N-1)/N * Sum((averageY - Y[i])^2))
    \param indicator whether value has been calculated,
    if false, then the arrays are empty.
*/
template <typename T>
T xydata<T>::SDMEAN_Y(bool &ok)
{
  if(n_values > 0)
    return SDY(ok)/sqrt(n_values);
  ok = false;
  return (T)(-1);
}

/** \brief get standart deviation of the mean value from X data array.
    Formula used: sigma = sqrt(1/(N-1)/N * Sum((averageX - X[i])^2))
    \param indicator whether value has been calculated,
    if false, then the arrays are empty.
*/
template <typename T>
T xydata<T>::SDMEAN_X(bool &ok)
{
  if(n_values > 0)
    return SDX(ok)/sqrt(n_values);
  ok = false;
  return (T)(-1);
}


/** \brief sum of Y values;
    \param indicator whether value has been calculated,
    if false, then the arrays are empty.
*/
template <typename T>
T xydata<T>::SUMY(bool &ok)
{
  ok = false;
  if(is_empty())
      return -1.0;
  
  ok = true;
  T sum = (T)0;
  for(size_t i = 0; i < n_values; i++)  sum += py[i];

  return sum;
}

/** \brief sum of X values;
    \param indicator whether value has been calculated,
    if false, then the arrays are empty.
*/
template <typename T>
T xydata<T>::SUMX(bool &ok)
{
  ok = false;
  if(is_empty())
      return -1.0;
  
  ok = true;
  T sum = (T)0;
  for(size_t i = 0; i < n_values; i++)  sum += px[i];
  return sum;
}

/**
   \return (true) if internal data pointers has not been allocated and set.
*/
template <typename T>
inline bool xydata<T>::is_empty() const
{
  //I usually trust this "indicator", coz it's set to false every time
  //when set_data(...) called or user invoked xydata<T> constructor
  // with non-NULL data pointers given in arguments.
  return (p_is_null || n_values < 1)? true : false;
}

/** Copy inner data into other object of the same class.
    
    \param destination of the data moving
    \return 0 on success.
*/
template <typename T>
inline int xydata<T>::copy_data(xydata<T> *result_xydata) const
{
  if(is_empty() || result_xydata==NULL) return -1;
  int res = result_xydata->set_data(this->n_values, this->px, this->py);
  return res;
  return 0;
}



/** \brief Copy N values from inner data into other object of the same class.
    \param non-NULL pointer to other object.
    \param start index.
    \param end index.
*/
template <typename T>
int xydata<T>::copy_nvalues(xydata<T> *result_xydata,
			    const size_t index_from, const size_t index_to) const
{
  if(is_empty() || result_xydata==NULL || index_to < index_from || index_from >= n_values || index_to >= n_values) return -1;
  int res = result_xydata->set_data((index_to - index_from), px + index_from, py + index_from);
  return res;
}

/** Copy Y data into the given std::vector.
    If the given list is not empty -- it will call their clear() method.
    
    \param destinating std::vector <T> to where data will be copied.
    \return 0 on success
*/
template <typename T>
inline int xydata<T>::copy_data(std::vector <T> &result) const
{
  if(!is_empty())
    {
      for(size_t i=0; i< n_values; i++)result.push_back(py[i]);
      return 0;
    }
  return -1;
}

/** Copy XY data into the given std::vectors.
    If the given lists are not empty -- it will call their clear() method.
    \param destinating std::vector <T> to where X-data will be copied.   
    \param destinating std::vector <T> to where Y-data will be copied. 
*/
template <typename T>
inline int xydata<T>::copy_data(std::vector <T> &result_x,
				std::vector <T> &result_y) const
{
  if(!is_empty())
    {
      if(!result_x.empty()) result_x.clear();
      if(!result_y.empty()) result_y.clear();
      for(size_t i=0; i< n_values; i++)
	{
	  result_x.push_back(px[i]);
	  result_y.push_back(py[i]);
	}
      return 0;
    }
  return -1;
}

/** Copy inner XY data into arrays of T values.
    \param counter: indicates how much was bytes copied.
    \param counter: indicates how much items bytes copied.
    \param target non-NULL pointer for X values.
    \param target non-NULL pointer for X values.
    \return 0 on success, -1 if empty or data pointer is NULL.
**/
template <typename T>
int xydata<T>::copy_data(size_t &bcount, size_t &icount, T *xdata, T *ydata) const
{
  if(is_empty() || xdata == NULL || ydata == NULL) return -1;
  bcount = n_values*sizeof(T);
  icount = n_values;
  memmove((void*)xdata, (void*)px, bcount);
  memmove((void*)ydata, (void*)py, bcount);
  
  return 0;
}

/** Copy inner X data into array of T values.
    \param counter: indicates how much was bytes copied.
    \param counter: indicates how much items bytes copied.
    \param target non-NULL pointer
    \return 0 on success, -1 if empty or data pointer is NULL.
**/
template <typename T>
int xydata<T>::copy_xdata(size_t &bcount, size_t &icount, T *data) const
{
  if(is_empty() || data == NULL) return -1;
  bcount = n_values*sizeof(T);
  icount = n_values;
  memmove((void*)data, (void*)px, bcount);
}

/** \brief Copy inner Y data into array of T values.
    \param counter: indicates how much was bytes copied.
    \param counter: indicates how much items bytes copied.
    \param target non-NULL pointer
    \return 0 on success, -1 if empty or data pointer is NULL.
**/
template <typename T>
int xydata<T>::copy_ydata(size_t &bcount, size_t &icount, T *data) const
{
  if(is_empty() || data == NULL) return -1;
  bcount = n_values*sizeof(T);
  icount = n_values;
  memmove((void*)data, (void*)py, bcount);
}


/**
   free internal pointers. sets n_values to 0.
   Yes, I use free(p) malloc, because filed to find a C++ replacement
   for such useful funtions like void *realloc(void *ptr, size_t size);
   
   \return always 0.
*/
template <typename T>
inline int xydata<T>::clear()
{
  if( !is_empty())
    {
      if(py!=NULL) free(py);
      if(px!=NULL) free(px);
      p_is_null = true;
      n_values = 0;
    }
  return 0;
}

/**
   Print to the terminal the contents of the buffers.
   If no parameters given -- I will use default format "[%lf,%lf]\t"
   and print 8 XY-values before newline.
   Function makes copy of (param1):  char *format_string,
   caller may delete it after usage.
   
   \param fromatting string, if NULL defaults are used.
   Caller is recommended to do not forget about \0 terminated character
   
   \param Number of columns, 8 by default.
   
   \return 0 i everything OK, -1 if no date has been set yet.*/

template <typename T>
inline int xydata<T>::print() const
{
  if( (p_is_null == true) || (py==NULL) || (px==NULL))
    {
#ifdef DEBUG
      std::cout << "int xydata_class::print(char *, int): Cannot print! Values are NULL\n";
#endif
      return -1;
    }
  size_t cnt = 0;
  while(cnt < n_values)
    {
      std::cout << px[cnt] << '\t' << py[cnt] << "\n";
      cnt++;
    }
  return 0;
}

/** Read array values from the file.
    \param filename.
    \param append
    whether to append to existing data:
    if true -- I append data to existing values(if there already are any),
    if false -- I use newly created inner arrays to keep values.
    \param max_read:
    maximum read values limitation.  if <=0 -- then no limit set.
    \return 0 if ok, -1 if file does not exist or it's unable for reading.
*/
template <typename T>
inline int xydata<T>::read_file (const std::string filename, bool append, size_t max_read)
{
  size_t read_count = 0;
  size_t  count = 0;
  const int chunk_size = 1024;
  T vx[chunk_size];
  T vy[chunk_size];
  
  std::ifstream stream;
  stream.open( filename.c_str(), std::ios::in );
  
  bool good = stream.good();
  if(!good)
    {
      stream.close();
      return -1;
    }
  if(!append) clear();
  size_t  limit = (max_read > 0)? max_read :  XYDATA_MAX_ARRAY_SIZE;
  while(good && count < limit && !stream.eof())
    {
      read_count = 0;
      do
	{
	  stream >> vx[read_count] >> vy[read_count];
	  read_count ++;
	  good = stream.good();
	}  while(good && read_count < chunk_size);
      //push px,py to xydata<T>:
      this->append((read_count-1), vx, vy);
      count += read_count;
    }
  
  stream.close();
  return 0;
}
  
/** Write array values to the file.
    \param filename.
    \param append:
    whether to append data to file instead of rewriting it:
    if true -- I append text to file, if false -- I recreate given file.
    \param max_read:
    maximum write values limitation. if 0 -- then no limit set.
*/
template <typename T>
inline int xydata<T>::write_file(const std::string filename, bool append, size_t max_write)
{
  int count      = 0;
  int good_index = 0;
  T v2[2];

  std::ofstream stream;
  if(append)
    stream.open( filename.c_str(), std::ios::app );
  else
    stream.open( filename.c_str(), std::ios::out );
  bool good = stream.good();
  if(!good)
    {
      stream.close();
      return -1;
    }
  size_t limit = (max_write > 0)? max_write : this->n_values;
  do
    {
      good_index = at(count, &v2[0]);
      stream << v2[0]<<'\t'<< v2[1]<<'\n';
      count ++;
    }  while(stream.good() && count < limit && good_index == 0);
  
  stream.close();
  return 0;

}

/** Output tab-separated values of arrays to stream.
    \param stream
    reference of the stream.
    
    \param data
    reference of the xydata<T>.
*/
template <typename T>
inline std::ostream &operator<<(std::ostream &stream, const xydata<T> &data)
{
  int count      = 0;
  int n_values   = data.length();
  int good_index = 0;
  T v2[2];
  do
    {
      good_index = data.at(count, &v2[0]);
      stream << v2[0]<< v2[1];
      count ++;
    }  while(stream.good() && count < n_values && good_index == 0);
  return stream;
}

/** Input values from stream into xydata<T>.
    It's assumed that ther're both X and Y values in stream:
    stream >> X >> Y;
    
    \param stream
    reference of the stream.
    
    \param data
    reference of the xydata<T>.
*/
template <typename T>
inline std::istream &operator>>(std::istream &stream, xydata<T> &data)
{
  size_t read_count = 0;
  size_t count = 0;
  const size_t chunk_size = 1024;
  T vx[chunk_size];
  T vy[chunk_size];
  
  bool good = stream.good();
  if(!good) return stream;
  while(good && count < XYDATA_MAX_ARRAY_SIZE && !stream.eof())
    {
      read_count = 0;
      do
	{
	  stream >> vx[read_count] >> vy[read_count];
	  read_count ++;
	  good = stream.good();
	}  while(good && read_count < chunk_size);
      //push px,py to xydata<T>:
      data.append((read_count-1), vx, vy);
      count += read_count;
    }
  return stream;
}


/** Return a pointer to internal buffer with X-data.
    \param reference of a variable to keep size of the pointer in bytes.
    \param reference of a variable to keep quantity of items in array pointed by pointer.
*/
template <typename T>
inline const T* xydata<T>::get_xpointer(size_t &bytes_count, size_t &items_count)
{
  bytes_count = n_values*sizeof(T);
  items_count = n_values;
  return const_cast<T*>(px);
}

/** Return a pointer to internal buffer with X-data.
    \param reference of a variable to keep size of the pointer in bytes.
    \param reference of a variable to keep quantity of items in array pointed by pointer.
   */
template <typename T>
inline const T* xydata<T>::get_ypointer(size_t &bytes_count, size_t &items_count)
{
  bytes_count = n_values*sizeof(T);
  items_count = n_values;
  return const_cast<T*>(py);
}

template <typename T>
xydata<T> * xydata<T>::make_Y_histogramm(bool &success)
{
  std::vector<T> values;
  std::vector<T> events;

  std::vector<T> temp;
  //copy Y values to vector:
  copy_data(temp);
  
  std::vector<size_t> remove_marks;
  size_t max_cycle = 1e06;
  size_t cycle_cnt = 0;

  while(temp.size() > 0 && cycle_cnt < max_cycle)
    {
      
      T value = temp[0];
      T event_count = 0;
      for(size_t cnt = 0; cnt < temp.size(); cnt++)
	{
	  if(qFuzzyIsNull(qAbs(temp[cnt] - value)))
	    {
	      event_count++;
	      remove_marks.push_back(cnt);
	    }
	}
      //create new bin in histogramm:
      values.push_back(value);
      events.push_back(event_count);
      
      //this will help to less and get more:
      //now clear out this value from temp vector:
      for(size_t cnt = 0; cnt < remove_marks.size(); cnt++)
	{
	  typename std::vector<T>::iterator rm_iter = (temp.begin() + remove_marks[cnt] - cnt);
	  if(rm_iter >= temp.begin() && rm_iter < temp.end())
	    {
	      temp.erase(rm_iter);
	    }
	}
      remove_marks.clear();
      //proceed to new value...
      cycle_cnt++;
    }
  if(values.empty() || events.empty()) 
    {
      success = false;
      return NULL;
    }
  
  xydata<T> *result = new xydata(values, events);
  values.clear();
  events.clear();
  temp.clear();
  return result;
}

template<typename T>
xydata<T> *xydata<T>::make_X_histogramm(bool &success)
{
  xydata<T> *temp = new xydata<T>(this);
  temp->swap_xy();
  bool ok = false;
  xydata<T> * xhisto = temp->make_Y_histogramm(ok);
  delete temp;
  success = (ok && xhisto != NULL);
  return xhisto;
}

#ifndef d_item_by_xy
#define d_item_by_xy
template<typename T>
struct item_by_x {
  // Default constructor will be needed if inserting into vector
  item_by_x(){v1 = 0; v2=0;}
  item_by_x(const T av1, const T av2){v1 = av1; v2 = av2;}
  
  // std::sort will require operator< to compile.
  bool operator < (item_by_x<T> const& rhs ) const
  { return v1 < rhs.v1; }
  T v1,v2;
};

template<typename T>
struct item_by_y {
  // Default constructor will be needed if inserting into vector
  item_by_y(){v1 = 0; v2=0;}
  item_by_y(const T av1, const T av2){v1 = av1; v2 = av2;}
  
  // std::sort will require operator< to compile.
  bool operator < (item_by_y<T> const& rhs ) const
  { return v2 < rhs.v2; }
  T v1,v2;
};
#endif

template<typename T>
void xydata<T>::sort_ascending_x()
{
  if(is_empty()) return;
  typename std::vector< item_by_x<T> > alldata;
  for(size_t cnt = 0; cnt < n_values; cnt++)
    alldata.push_back( item_by_x<T>( px[cnt], py[cnt]) );
  sort(alldata.begin(), alldata.end());
  
  for(size_t cnt = 0; cnt < n_values; cnt++)
    {
      item_by_x<T> item = alldata[cnt];
      px[cnt] = item.v1;
      py[cnt] = item.v2;
    }
  alldata.clear();
}

template<typename T>
void xydata<T>::sort_ascending_y()
{
  if(is_empty()) return;
  typename std::vector< item_by_y<T> > alldata;
  for(size_t cnt = 0; cnt < n_values; cnt++)
    alldata.push_back( item_by_y<T>( px[cnt], py[cnt]) );
  sort(alldata.begin(), alldata.end());
  
  for(size_t cnt = 0; cnt < n_values; cnt++)
    {
      item_by_y<T> item = alldata[cnt];
      px[cnt] = item.v1;
      py[cnt] = item.v2;
    }
  alldata.clear();
}


template<typename T>
void xydata<T>::sort_descending_x()
{
  if(is_empty()) return;
  sort_ascending_x();
  revert_values_order();
}

template<typename T>
void xydata<T>::sort_descending_y()
{
  if(is_empty()) return;
  sort_ascending_y();
  revert_values_order();
}

template<typename T>
void xydata<T>::revert_values_order()
{
  typename std::vector<T> vx, vy;
  copy_data(vx, vy);
  std::reverse(vx.begin(), vx.end());
  std::reverse(vy.begin(), vy.end());
  set_data(vx, vy);
}

template<typename T>
void xydata<T>::swap_xy()
{
  if(is_empty()) return;
  T *p = px;
  px = py;
  py = p;
}


#endif//XYDATA_TEMPLATE_H

