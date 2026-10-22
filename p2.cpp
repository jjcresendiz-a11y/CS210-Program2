#include "request.h"
#include "webserver.cpp"
#include "loadbalancer.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

const int NUM_SERVERS = 5;
static int ps = 0;               // the process ID incrementer

request createRandomRequest()
{
   stringstream ips, ipd;
   request r;

   // For example, 12.243.87.112
   ips << (rand() % 256) << "." << (rand() % 256) << "."
       << (rand() % 256) << "." << (rand() % 256);
   ipd << (rand() % 256) << "." << (rand() % 256) << "."
       << (rand() % 256) << "." << (rand() % 256);

   r.source = ips.str();
   r.destination = ipd.str();
   r.processTime = rand() % 500;
   r.pid = ++ps;
   return r;
}

int main()
{
   // Set the seed for random number generation.
   srand(time(NULL));

   // Create a load balancer.
   loadbalancer lb;

   // Start off with a "full" queue.
   for (int i = 0; i < 10; i++)
   {
      lb.addRequest(createRandomRequest());
   }

   // Create an array of webservers, each with an initial request.
   webserver webarray[NUM_SERVERS];
   for (int i = 0; i < NUM_SERVERS; i++)
   {
      webserver w(static_cast<char>(i + 65));
      webarray[i] = w;
      webarray[i].addRequest(lb.getRequest(), lb.getTime());
   }

   // Run the simulation.
   while (lb.getTime() < 10000)
   {
      int currTime = lb.getTime();
      int size = lb.getSize();
      int serverIndex = currTime % NUM_SERVERS;

      if (webarray[serverIndex].isRequestDone(currTime))
      {
         request r = webarray[serverIndex].getRequest();

         cout << "Finished at " << currTime << " "
              << webarray[serverIndex].getName();
         cout << " pid " << r.pid << "/" << size
              << " process time was " << r.processTime;
         cout << " processed request from " << r.source
              << " to " << r.destination << endl;

         // Give the webserver its next request.
         webarray[serverIndex].addRequest(lb.getRequest(), currTime);
      }

      // Occasionally add a new request to the load balancer.
      if (rand() % 10 == 0)
      {
         lb.addRequest(createRandomRequest());
      }

      lb.incTime();
   }

   return 0;
}
