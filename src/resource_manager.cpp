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

#define MAX_RESOURCE_OBJS_OF_ONE_TYPE 20

#define TYPE_A_ID 0
#define TYPE_B_ID 1
#define TYPE_C_ID 2

#define RESOURCE_TYPE_TABLE(_, __, ___) \
    _(TYPE_A_ID, ResourceTypeA, __, ___) \
    _(TYPE_B_ID, ResourceTypeB, __, ___) \
    _(TYPE_C_ID, ResourceTypeC, __, ___) 

struct ResourceTypeA : public Resource{
	static int getTypeId(){return TYPE_A_ID;};
    ResourceTypeA(int index):Resource(index){};
    void realTypeBusiness(){cout << "this is business of type A. index is " << getIndex()  << endl;};
};

struct ResourceTypeB : public Resource{
	static int getTypeId(){return TYPE_B_ID;};
    ResourceTypeB(int index):Resource(index){};
    void realTypeBusiness(){cout << "this is business of type B. index is " << getIndex() << endl;};
};

struct ResourceTypeC : public Resource{
	static int getTypeId(){return TYPE_C_ID;};
    ResourceTypeC(int index):Resource(index){};
    void realTypeBusiness(){cout << "this is business of type C. index is " << getIndex()  << endl;};
};

struct ResourcePool{
    int type_id;
    Resource* ro[MAX_RESOURCE_OBJS_OF_ONE_TYPE];
};

#define CREATE_RESOURCE(type_id, Type, res_index, res) \
    case type_id: {   \
        res = (Resource*) (new Type(res_index)); \
        break; \
    }

#define CREATE_RESOURCE_POOL(type_id, Type, _, __) {type_id, NULL},

ResourcePool resourcePool[] = {RESOURCE_TYPE_TABLE(CREATE_RESOURCE_POOL, NULL, NULL)};


void CreateOneResourceType(int type_id, int res_index){
    Resource* res = NULL;
    switch(type_id) {
        RESOURCE_TYPE_TABLE(CREATE_RESOURCE, res_index, res);
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
                CreateOneResourceType(TYPE_A_ID, 1);
                CreateOneResourceType(TYPE_B_ID, 1);
                break;
            }
            case REPOSITORY_TYPE_TWO: {
                CreateOneResourceType(TYPE_A_ID, 2);
                CreateOneResourceType(TYPE_B_ID, 2);
                CreateOneResourceType(TYPE_C_ID, 2);
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



