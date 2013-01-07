// queue.h (Queue)

template<class Object> class Queue         // Object is a type to be specified by user
{
public:

      Queue()                              // constructor
       : _front(0),                        // 0 pointer indicates end of queue
         _back(0)
      {}

      ~Queue()                             // destructor
      {
            clear();
      }

      bool is_empty()
      {
            return _front == 0;
      }

      void clear()
      {
            while (_front != 0)
            {
               pop_front();
            }
      }

      void push_back(Object object)         // insert object at end of queue
      {
            Item * cur = new Item(object);  // get new memory for Item at address cur,
                                            // initialize with object and NULL pointer
            if (is_empty()) 
            {
                  _back = cur;
                  _front = cur;
            } 
            else 
            {
                  _back->_next = cur;       // p->n is abbreviation for (*p).n
                  _back = cur;
            }
      }

      Object pop_front()                    // delete and return first object of queue
      {                                     // ATTENTION: queue must not be empty!
            Item * cur = _front;
            if (_back == _front) 
            {
                  _front = 0;
                  _back  = 0;
            } 
            else 
            {
                  _front = _front->_next;       
            }
            Object object = cur->_object;
            delete cur;                      // free memory for 1 Item at address cur
            return object;
      }

private:

      struct Item                          // struct is same as class, except that
      {                                    // per default, everything is public
            Item(Object object)      
             : _object(object),            // Object (the template parameter)
               _next(0)                 // must have appropriate constructor
            {}

            Object _object;                // Item contains an Object and a
            Item * _next;                  // pointer to the next Item (or 0)
      };

      Item * _front;                       // _front and _back are pointers to 
      Item * _back;                        // variables of type Item (defined above),
};                                         // or the 0 pointer if queue is empty

