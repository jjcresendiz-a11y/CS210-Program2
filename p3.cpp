#include "request.h"
#include "webserver.cpp"
#include "loadbalancer.h"

#include <iostream>
#include <cstdlib>
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
   // A fixed seed makes every run deterministic for comparison and grading.
   srand(1);

   // Create a load balancer.
   loadbalancer lb;

   // Start off with a "full" queue.
   for (int i = 0; i < 10; i++)
   {
      request r = createRandomRequest();
      lb.addRequest(r);
   }

   // Create an array of webservers, each with an initial request.
   webserver webarray[NUM_SERVERS];
   for (int i = 0; i < NUM_SERVERS; i++)
   {
      webserver w((char) (i + 65));
      webarray[i] = w;
      webarray[i].addRequest(lb.getRequest(), lb.getTime());
   }

   // Run the simulation.
   while (lb.getTime() < 10000)
   {
      int currTime = lb.getTime();
      int size = lb.getSize();

      // Check whether the selected webserver has finished its request.
      if (webarray[currTime % NUM_SERVERS].isRequestDone(currTime))
      {
         request r = webarray[currTime % NUM_SERVERS].getRequest();

         cout << "Finished at " << currTime << " "
              << webarray[currTime % NUM_SERVERS].getName();
         cout << " pid " << r.pid << "/" << size
              << " process time was " << r.processTime << endl;

         // Give the webserver its next request.
         webarray[currTime % NUM_SERVERS].addRequest(lb.getRequest(), currTime);
      }

      // Occasionally add a new request to the load balancer.
      if (rand() % 10 == 0)
      {
         request r = createRandomRequest();
         lb.addRequest(r);
      }

      lb.incTime();
   }

   return 0;
}
