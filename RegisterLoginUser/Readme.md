# Register and Login of Users using MVC (with static data)

This is a simple project to experiment with Model View Controller using C++.

I try to replay a normal Login and register user

## Details

- I dont implement Data base with C++ yet, so in this case i used a STATIC list to have a common data between Register and User model
- I implement the architectural pattern MVC (Model View Controller)
- I used inherence to all models inherit fron a base model that contains the STATIC list
- All controllers are using the same view to input and output data, cause was unnecessary other view