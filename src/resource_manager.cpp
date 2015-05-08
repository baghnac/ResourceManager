#include <iostream>
using namespace std;

#define REPOSITORY_INVALID 0
#define REPOSITORY_TYPE_ONE 1
#define REPOSITORY_TYPE_TWO 2

struct Resource{
    Resource(int index){index_ = index;};
    int getIndex(){return index_;};
    virtual void realTypeBusiness() = 0;
private:
    int index_;
};

#define TOTAL_RESOURCE_TYPE 3
#define MAX_RESOURCE_OBJS_OF_ONE_TYPE 20

#define TYPE_A_ID 0
#define TYPE_B_ID 1
#define TYPE_C_ID 2

struct ResourceTypeA : public Resource{
	static int getTypeId(){return TYPE_A_ID;};
    ResourceTypeA(int index):Resource(index){};
    void realTypeBusiness(){cout << "this is business of type A " << endl;};
};

struct ResourceTypeB : public Resource{
	static int getTypeId(){return TYPE_B_ID;};
    ResourceTypeB(int index):Resource(index){};
    void realTypeBusiness(){cout << "this is business of type B " << endl;};
};

struct ResourceTypeC : public Resource{
	static int getTypeId(){return TYPE_C_ID;};
    ResourceTypeC(int index):Resource(index){};
    void realTypeBusiness(){cout << "this is business of type C " << endl;};
};

struct ResourcePool{
    Resource* ro[MAX_RESOURCE_OBJS_OF_ONE_TYPE];
};

ResourcePool resourcePool[TOTAL_RESOURCE_TYPE] = {0};

void CreateOneResourceType(int type_id, int res_index){
    Resource* res = NULL;
    switch(type_id) {
        case 0: {
            res = (Resource*) (new ResourceTypeA(res_index));
            break;
        }
        case 1: {
            res = (Resource*) (new ResourceTypeB(res_index));
            break;
        }
        case 2: {
            res = (Resource*) (new ResourceTypeC(res_index));
            break;
        }
		default: {
            break;
        }
    }
    if(res){
        resourcePool[type_id].ro[res_index] = res;
    }
}

void CreateRepResources(int rep_id[], int rep_num){
     for(long loop = 0; loop < rep_num; loop++){
        switch (rep_id[loop]) {
            case REPOSITORY_TYPE_ONE: {
                CreateOneResourceType(ResourceTypeA::getTypeId(), 1);
                CreateOneResourceType(ResourceTypeB::getTypeId(), 1);
                break;
            }
            case REPOSITORY_TYPE_TWO: {
                CreateOneResourceType(ResourceTypeA::getTypeId(), 2);
                CreateOneResourceType(ResourceTypeB::getTypeId(), 2);
                CreateOneResourceType(ResourceTypeC::getTypeId(), 2);
                break;
            }
        }
     }
}

void GetRoAndRunBusiness(int type_id, int res_index){
    Resource* res = resourcePool[type_id].ro[res_index];
    if(res) res->realTypeBusiness();
}

int main()
{
    int  rep_id[2] = {REPOSITORY_TYPE_ONE, REPOSITORY_TYPE_TWO};  // resource repository id
	CreateRepResources(rep_id, sizeof(rep_id));
	GetRoAndRunBusiness(ResourceTypeB::getTypeId(), 2);
    return 0;
}



