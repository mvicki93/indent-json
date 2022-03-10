#include <stdio.h>
int end_index_monitor = 0;
char* json_formatter(char *json);
void p_space(char *f_json, int blank)
 {
    int k;
    for (k=0; k<blank; ++k) {
       f_json[end_index_monitor++] = ' ';
    }
    f_json[end_index_monitor] = '\0';
}
int main()
{
   char json[88000] = "[{\"self\":\"Self-1\",\"site\":0,\"sname\":\"\",\"fi\":\"\",\"b-um\":0,\"ps-shlf\":0,\"location\":\"\",\"subt-name\":\"\",\"ne-id\":0,\"mary-p\":\"0.0.0.0\",\"mary\":\"DISABLE\",\"dc\":\"DISABLE\",\"clus\":\"DISABLE\",\"ext-sf\":\"DISABLE\",\"a-ftimer\":\"DISABLE\",\"f-timer\":0,\"db-state\":\"INSYNC\",\"shsync\":\"TRUE\"}]";
   //beautify_json(json);
   char *r_json = json_formatter(json);
   //printf("%s\n\n", json);
   printf("%s\n\n", r_json);
}

char* my_strcat(char* destination, const char* source)
{
    // make `ptr` point to the end of the destination string
    char* ptr = destination + strlen(destination);
 
    // appends characters of the source to the destination string
    while (*source != '\0') {
        *ptr++ = *source++;
        end_index_monitor++;
    }
 
    // null terminate destination string
    *ptr = '\0';
    //end_index_monitor++;
    // the destination is returned by standard `strcat()`
    return destination;
}

char* json_formatter(char *json)
{
	char *f_json = NULL;
	int j_len = 0, i = 0;
	int space = 0;
	/* create tmp malloc for store formatted data */
	f_json = malloc(888000);
	if (f_json == NULL) {
		printf("malloc faild for allocate memory for f_json\n");
		exit(1);
	}
	j_len = strlen(json);

	while (json[i] != '\0') {
		/* handle the case of  */
		if (json[i] == '{') {
			my_strcat(f_json, "{\n");
			space += 4;
			p_space(f_json, space);         
			i++;
		} else if (json[i] == '[') {
                        my_strcat(f_json, "[\n");
                        space += 4;
                        p_space(f_json, space);
                        i++;
                }
		/* handle quote case */
		if (json[i] == '\"') {
			/* copy all key */
			my_strcat(f_json, "\"");
			i++;
			while (json[i] != '\"') {
				f_json[end_index_monitor++] = json[i];
                                i++; 
			}
                        f_json[end_index_monitor++] = json[i];
                        i++;
			f_json[end_index_monitor] = '\0';
			if (json[i] == ':') {
				f_json[end_index_monitor++] = json[i];
                                i++;
				/* after : we need to find value is string or dic, list */
				if (json[i] == '[') {/* list */
					my_strcat(f_json, "[\n");
					space += 4;
					p_space(f_json, space);
					i++;
				} else if (json[i] == '{') { /* dic */
					my_strcat(f_json, "{\n");
					space += 4;
					p_space(f_json, space);
                                        //printf("vicki %d\n", space);
					i++;             
				} else if (json[i] == '\"') { /*str*/
					my_strcat(f_json, "\"");
					i++;
					while (json[i] != '\"') {
						f_json[end_index_monitor++] = json[i];
                                                i++;
					}
                                        f_json[end_index_monitor++] = json[i];
                                        i++;
					f_json[end_index_monitor] = '\0';
				} else {  /* value */
                                       while (json[i] != ',') {
                                           f_json[end_index_monitor++] = json[i];
                                           i++;
                                           if (json[i] == '}' || json[i] == ']')
                                               break;    
                                       }
                                       f_json[end_index_monitor] = '\0';  
                                }
			      
		       }
		if (json[i] == ',') {
			my_strcat(f_json, ",\n");
			p_space(f_json, space);
                        //printf("%s\n", f_json);
                        i++;
		}
		if (json[i] == '}' && json[i +1] == ',') {
			space -= 4;
                        my_strcat(f_json, "\n");
			p_space(f_json, space);
			my_strcat(f_json, "},\n");
                        p_space(f_json, space);
                        i = i + 2;
		} else if (json[i] == '}') {
			space -= 4;
                        my_strcat(f_json, "\n");
			p_space(f_json, space);
			my_strcat(f_json, "}\n");
                        p_space(f_json, space);
                        i++;
		}
                if (json[i] == ']' && json[i +1] == ',') {
			space -= 4;
                        my_strcat(f_json, "\n");
			p_space(f_json, space);
			my_strcat(f_json, "],\n");
                        p_space(f_json, space);
                        i = i + 2;
		} else if (json[i] == ']') {
			space -= 4;
                        my_strcat(f_json, "\n");
			p_space(f_json, space);
			my_strcat(f_json, "]\n");
                        p_space(f_json, space);
                        i++;
		}


	} else if (json[i] == '}' && json[i +1] == ',') {
             space -= 4;
             my_strcat(f_json, "\n");
             p_space(f_json, space);
             my_strcat(f_json, "},\n");
             p_space(f_json, space);
             i = i + 2;
        }else if (json[i] == '}') {
             space -= 4;
             my_strcat(f_json, "\n");
             p_space(f_json, space);
             my_strcat(f_json, "}\n");
             p_space(f_json, space);
             i++;
        }
        if (json[i] == ']' && json[i +1] == ',') {
             space -= 4;
             my_strcat(f_json, "\n");
             p_space(f_json, space);
             my_strcat(f_json, "],\n");
             p_space(f_json, space);
             i = i + 2;
        } else if (json[i] == ']') {
             space -= 4;
             my_strcat(f_json, "\n");
             p_space(f_json, space);
             my_strcat(f_json, "]\n");
             p_space(f_json, space);
             i++;
             //printf("%s\n", f_json);
        }
    } 
//        f_json[end_index_monitor] = '\0';
//        printf("%s\n",f_json);
        return f_json;
}




