# Authentication and Authorization Platform for Home Automation System

## Services
### Cloud Authentication Service
1. Lives on cloud, verifies the identity of a person

### Cloud Authorization Service
1. Lives on cloud, checks what roles a person has, and whether any of these role
has permission for performing a required action on a resource

### Local Authorization Service
1. Responsibilities same as cloud authorization service, but only for those responsibilities that are 
required locally inside a home network


## Code guideline 
1. Make use of MoleculerJS, and all these services and functions, should be moleculerjs services and 
moleculerjs actions

2. Permissions can be of the form of 