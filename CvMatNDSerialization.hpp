/*
 * FILE:   CvMatNDSerialization.h
 *
 * AUTHOR: Jinchao Liu 
 * DATE:   27/11/2012
 *
 * BRIEF:  Serialize an OpenCV data structure cv::MatND using  
 *         boost::serialization library.
 * USAGE:  
 *		  // save 
 *		  cv::MatND hist;
 *		  std::ofstream ofs("hist.cvmatnd", std::ios::out | std::ios::binary);
 * 		  { 
 *			boost::archive::binary_oarchive oa(ofs);
 *			oa << hist;
 *		  }
 *		  ofs.close();
 *
 *		  // load 
 *		  cv::MatND reloadedHist;
 *		  std::ifstream ifs("hist.cvmatnd", std::ios::binary);
 *		  { 
 *			boost::archive::binary_iarchive oa(ifs);
 *			oa >> reloadedHist;
 *		  }
 *		  ifs.close();
*/
#ifndef CVMATNDSERIALIZATION_H
#define CVMATNDSERIALIZATION_H
// OpenCV
//#include <opencv2/opencv.hpp>
#include <cv.h>   		

// STD & STL 
#include <vector>
#include <fstream>

// boost
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>


BOOST_SERIALIZATION_SPLIT_FREE(cv::MatND)
namespace boost {
  namespace serialization {

	// save
    template<class Archive>
    void save(Archive & ar, const cv::MatND& mnd, const unsigned int version)
    {
		size_t elemSize  = mnd.elemSize();
		size_t elemSize1 = mnd.elemSize1();
		int channels     = mnd.channels();
		int depth        = mnd.depth();
		int type         = mnd.type();
		int dims         = mnd.dims;

		ar & elemSize;
		ar & elemSize1;
		ar & channels;
		ar & depth;
		ar & type;
		ar & dims;

		size_t elemNumber = 1;
		for (int i = 0; i < dims; i++)
		{
			ar & mnd.size[i];
			elemNumber = elemNumber * mnd.size[i]; // how many elements in total
		}

		const size_t dataSize = elemNumber * elemSize;
		ar & boost::serialization::make_array(mnd.data, dataSize);
    }

	// load
    template<class Archive>
    void load(Archive & ar, cv::MatND& mnd, const unsigned int version)
    {
		size_t elemSize, elemSize1;
		int channels, depth, type, dims;

		ar & elemSize;
		ar & elemSize1;
		ar & channels;
		ar & depth;
		ar & type;
		ar & dims;

		mnd.dims = dims;
		
		int* size = new int[dims];

		size_t elemNumber = 1;
		for (int i = 0; i < dims; i++)
		{
			ar & size[i];
			elemNumber = elemNumber * size[i]; // how many elements in total
		}

		mnd.create(dims, size, type);
		const size_t dataSize = elemNumber * elemSize;
		ar & boost::serialization::make_array(mnd.data, dataSize);

		delete size;
	}
  } // namespace serialization
} // namespace boost
#endif