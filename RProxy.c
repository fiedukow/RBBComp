#include <dlfcn.h>

/** Possbile status values */
#define STATUS_ERROR 0
#define STATUS_SUCCESS 1

/** libbbcomp.so reference **/
void* LIB_BBCOMP = 0;

/** Functions from libbbcomp **/
int(*BB_configure)(int, const char*) = 0;
int(*BB_login)(const char* username, const char* password) = 0;
int(*BB_numberOfTracks)(void) = 0;
const char*(*BB_trackName)(int) = 0;
int(*BB_setTrack)(const char*) = 0;
int(*BB_numberOfProblems)(void) = 0;
int(*BB_setProblem)(int) = 0;
int(*BB_dimension)(void) = 0;
int(*BB_budget)(void) = 0;
int(*BB_evaluations)(void) = 0;
int(*BB_evaluate)(double*, double*) = 0;
int(*BB_history)(int, double*, double*) = 0;
const char*(*BB_errorMessage)(void) = 0;

/**
 * Gets function pointers from *.so"
 **/
void R_init(int* status) {
  *status = STATUS_SUCCESS;

  LIB_BBCOMP = dlopen("libbbcomp.so", RTLD_LAZY);
  if (!LIB_BBCOMP) goto fail;
  BB_login = dlsym(LIB_BBCOMP, "login");
  if (!BB_login) goto fail;
  BB_numberOfTracks = dlsym(LIB_BBCOMP, "numberOfTracks");
  if (!BB_numberOfTracks) goto fail;
  BB_trackName = dlsym(LIB_BBCOMP, "trackName");
  if (!BB_trackName) goto fail;
  BB_setTrack = dlsym(LIB_BBCOMP, "setTrack");
  if (!BB_setTrack) goto fail;
  BB_numberOfProblems = dlsym(LIB_BBCOMP, "numberOfProblems");
  if (!BB_numberOfProblems) goto fail;
  BB_setProblem = dlsym(LIB_BBCOMP, "setProblem");
  if (!BB_setProblem) goto fail;
  BB_dimension = dlsym(LIB_BBCOMP, "dimension");
  if (!BB_dimension) goto fail;
  BB_budget = dlsym(LIB_BBCOMP, "budget");
  if (!BB_budget) goto fail;
  BB_evaluations = dlsym(LIB_BBCOMP, "evaluations");
  if (!BB_evaluations) goto fail;
  BB_evaluate = dlsym(LIB_BBCOMP, "evaluate");
  if (!BB_evaluate) goto fail;
  BB_history = dlsym(LIB_BBCOMP, "history");
  if (!BB_history) goto fail;
  BB_errorMessage = dlsym(LIB_BBCOMP, "errorMessage");
  if (!BB_errorMessage) goto fail;

  return;

fail:
  *status = STATUS_ERROR;
  return;
}

void R_login(char** log, char** pass, int* status) {
  if (!LIB_BBCOMP || !BB_login) {
    *status = STATUS_ERROR;
    return;
  }

  *status = (BB_login(*log, *pass) != 0) ? STATUS_SUCCESS : STATUS_ERROR;
}

void R_numberOfTracks(int* noTracks, int* status) {
  if (!LIB_BBCOMP || !BB_numberOfTracks) {
    *status = STATUS_ERROR;
    return;
  }

  *noTracks = BB_numberOfTracks();
  *status = ((*noTracks) != 0) ? STATUS_SUCCESS : STATUS_ERROR;
}

void R_trackName(int* trackIndex, const char** name, int* status) {
  if (!LIB_BBCOMP || !BB_trackName) {
    *status = STATUS_ERROR;
    return;
  }

  *name = BB_trackName(*trackIndex);
  *status = (*name) ? STATUS_SUCCESS : STATUS_ERROR;
}

void R_setTrack(const char** name, int* status) {
  if (!LIB_BBCOMP || !BB_setTrack) {
    *status = STATUS_ERROR;
    return;
  }

  *status = (BB_setTrack(*name) != 0) ? STATUS_SUCCESS : STATUS_ERROR;
}

void R_numberOfProblems(int* n, int* status) {
  if (!LIB_BBCOMP || !BB_numberOfProblems) {
    *status = STATUS_ERROR;
    return;
  }

  *n = BB_numberOfProblems();
  *status = (*n != 0) ? STATUS_SUCCESS : STATUS_ERROR;
}

void R_setProblem(int* id, int* status) {
  if (!LIB_BBCOMP || !BB_setProblem) {
    *status = STATUS_ERROR;
    return;
  }

  *status = (BB_setProblem(*id) != 0) ? STATUS_SUCCESS : STATUS_ERROR;
}

void R_dimension(int* n, int* status) {
  if (!LIB_BBCOMP || !BB_dimension) {
    *status = STATUS_ERROR;
    return;
  }

  *n = BB_dimension();
  *status = (*n != 0) ? STATUS_SUCCESS : STATUS_ERROR;
}

void R_budget(int* n, int* status) {
  if (!LIB_BBCOMP || !BB_budget) {
    *status = STATUS_ERROR;
    return;
  }

  *n = BB_budget();
  *status = (*n != 0) ? STATUS_SUCCESS : STATUS_ERROR;
}

void R_evaluations(int* n, int* status) {
  if (!LIB_BBCOMP || !BB_evaluations) {
    *status = STATUS_ERROR;
    return;
  }

  *n = BB_evaluations();
  *status = (*n != -1) ? STATUS_SUCCESS : STATUS_ERROR;
}

void R_evaluate(double* point, double* value, int* data_length, int* status) {
  if (!LIB_BBCOMP || !BB_evaluate) {
    *status = STATUS_ERROR;
    return;
  }

  const int n = BB_dimension();
  if (*data_length % n != 0 || *data_length <= 0 || n <= 0) {
    *status = STATUS_ERROR;
    return;
  }
  const int points = *data_length / n;
  int i;
  for (i = 0; i < points; ++i) {
    if (BB_evaluate(point + (i*n), value + i) == 0)
      break;
  }

  *status = i;
  return;
}

void R_history(int* index, double* point, double* value, int* data_length, int* status) {
  if (!LIB_BBCOMP || !BB_history || *index >= BB_evaluations()) {
    *status = STATUS_ERROR;
    return;
  }

  const int n = BB_dimension();
  if (*data_length % n != 0 || *data_length <= 0 || n <= 0) {
    *status = STATUS_ERROR;
    return;
  }
  const int points = *data_length / n;
  int i;
  for (i = 0; i < points; ++i) {
    if (BB_history(*(index + i), point + (i*n), value + i) == 0)
      break;
  }

  *status = i;
  return;
}

