EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues){
    lineLengthNode lengthNode = malloc(sizeof(*lengthNode));
    if (lengthNode == NULL) {
        return NULL;
    }
    lineLengthNode beforeFinishing,nextLengthNode, iteLengthNode = lengthNode;
    char s;
    while ((s = fgetc(queues)) != EOF) {
        int lineLength = 0;
        while (s != NEW_LINE) {
            lineLength++;
            s = fgetc(queues);
            if(s==EOF){
                break;
            }
        }
        iteLengthNode->length = lineLength;
        nextLengthNode = malloc(sizeof(*nextLengthNode));
        if (nextLengthNode == NULL) {
            free(lengthNode);
            return NULL;
        }
        nextLengthNode->next=NULL;
        beforeFinishing=iteLengthNode;
        iteLengthNode->next = nextLengthNode;
        iteLengthNode = nextLengthNode;
    }
    free(iteLengthNode);
    beforeFinishing->next=NULL;
    rewind(queues);
    int countWords = 0;
    char *space1 = " ";
    char *splitStrings;
    char *queueDataBuffer = malloc(lengthNode->length);
    if(queueDataBuffer==NULL){
        free(lengthNode);
        free(nextLengthNode);
        return NULL;
    }
    coursesNode courseIte=NULL;
    studentsNode studentIte=NULL;
    IsraeliQueueError result;
    IsraeliQueue queueCopy=NULL;
    int lineSize = lengthNode->length;
    iteLengthNode = lengthNode;
    while (fgets(queueDataBuffer, lineSize+2, queues) != NULL) {
        splitStrings = strtok(queueDataBuffer, space1);
        while (splitStrings != NULL) {
            countWords++;
            if (countWords == 1) {
                courseIte = searchCourseById( atoi(splitStrings),sys->coursesInfo);
            }
            else {
                studentIte = searchStudentList(sys->studentsInfo, atoi(splitStrings));
                queueCopy=IsraeliQueueClone(courseIte->courseQueue);
                result = IsraeliQueueEnqueue(courseIte->courseQueue, ((void *) studentIte));
                if (result != ISRAELIQUEUE_SUCCESS) {
                    free(lengthNode);
                    free(nextLengthNode);
                    free(queueDataBuffer);
                    IsraeliQueueDestroy(courseIte->courseQueue);
                    courseIte->courseQueue=queueCopy;
                    return NULL;
                }
            }
            splitStrings = strtok(NULL, space1);
        }
        iteLengthNode = iteLengthNode->next;
        if(iteLengthNode){
            lineSize = iteLengthNode->length;
        }
        countWords=0;
    }
    lineLengthNode prev=NULL, toDelete = lengthNode;
    while (toDelete) {
        prev = toDelete;
        toDelete = toDelete->next;
        free(prev);
    }
    IsraeliQueueDestroy(queueCopy);
    return sys;
}