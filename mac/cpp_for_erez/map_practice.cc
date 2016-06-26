#include <map>
#include <iostream>

struct box {

  double _min_x, _min_y, _max_x, _max_y;

  box() { _min_x = _min_y = _max_x = _max_y = 0.; }
  
  box(double min_x, double min_y, double max_x, double max_y)
    : _min_x(min_x), _min_y(min_y), _max_x(max_x), _max_y(max_y)
  {}
      
};

int main()
{
  std::map<int,std::map<int,std::map<int,box> > > my_map;

  box b1(0,0,0,0);
  box b2(1,1,1,1);
  box b3(2,2,2,2);

  // b1 in (run,subrun,event) = (0,0,0)
  my_map[0][0][0]=b1;
  // b2 in (run,subrun,event) = (3,1,1)
  my_map[3][1][1]=b2;
  // b3 in (run,subrun,event) = (0,1,1)
  my_map[0][1][1]=b3;

  // Now let's search
  for(size_t run=0; run<3; run++) {

    //Search run
    auto run_iter = my_map.find(run);
    if(run_iter == my_map.end()) {
      std::cout << " run " << run << " not found..." << std::endl;
      continue;
    }

    // Grab run-map's value (i.e. subrun map)
    auto const& subrun_map = (*run_iter).second;

    for(size_t subrun=0; subrun<3; subrun++) {

      //Search sub run
      auto subrun_iter = subrun_map.find(subrun);
      if(subrun_iter == subrun_map.end()) {
	std::cout << " subrun " << subrun << " not found..." << std::endl;
	continue;
      }
      
      // Grab subrun-map's value (i.e. event map)
      auto const& event_map = (*subrun_iter).second;
      
      for(size_t event=0; event<3; event++) {

	// Search event
	auto event_iter = event_map.find(event);
	if(event_iter == event_map.end()) {
	  std::cout << " event " << event << " not found..." << std::endl;
	  continue;
	}

	// Grab box
	auto const& b = (*event_iter).second;
	
	std::cout << "(run,subrun,event) = (" << run << "," << subrun << "," << event << ") ... "
		  << " found box (" << b._min_x << "," << b._min_y
		  << ") => ("
		  << b._max_x << "," << b._max_y << ")" << std::endl;
      }
    }
  }
  return 0;
}
