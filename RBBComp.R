#Configure = function
Login = function(login, password) {
  dyn.load("RProxy.so", local=FALSE)
  INIT = .C("R_init", status=as.integer(0))
  if (INIT$status == 0)
    return(0)
  LOGIN = .C("R_login", log = as.character(login), pass = as.character(password), status = as.integer(0))
  return(LOGIN$status)
}

NumberOfTracks = function() {
  NO_TRACKS = .C("R_numberOfTracks", noTracks = as.integer(0), status = as.integer(0))
  if (NO_TRACKS$status == 0)
    return(0)
  return(NO_TRACKS$noTracks)
}

TrackName = function(index) {
  T_NAME = .C("R_trackName", trackIndex=as.integer(index), name=as.character(""), status = as.integer(0))
  if (T_NAME$status == 0)
    return("")
  return(T_NAME$name)
}

SetTrack = function(t_name) {
  SET_TRACK = .C("R_setTrack", name=as.character(t_name), status = as.integer(0))
  return(SET_TRACK$status)
}

NumberOfProblems = function() {
  NO_PROBLEMS = .C("R_numberOfProblems", n = as.integer(0), status = as.integer(0))
  if (NO_PROBLEMS$status == 0)
    return(-1)
  return(NO_PROBLEMS$n)
}

SetProblem = function(n) {
  SET_PROBLEM = .C("R_setProblem", n = as.integer(n), status = as.integer(0))
  return(SET_PROBLEM$status)
}

Dimension = function() {
  DIM = .C("R_dimension", n = as.integer(0), status = as.integer(0))
  if (DIM$status == 0)
    return(0)
  return(DIM$n)
}

Budget = function() {
  BUDGET = .C("R_budget", n = as.integer(0), status = as.integer(0))
  if (BUDGET$status == 0)
    return(0)
  return(BUDGET$n)
}

Evaluations = function() {
  EVALUATIONS = .C("R_evaluations", n = as.integer(0), status = as.integer(0))
  if (EVALUATIONS$status == 0)
    return(0)
  return(EVALUATIONS$n)
}

Evaluate = function(points) {
  N = max(1, nrow(points))
  EVAL = .C("R_evaluate", point = as.double(points), value = as.double(rep(1e100, N)), data_length=length(points), status = as.integer(0))
  if (EVAL$status < N)
    warning("Not all of requested points were calculated correctly.")
  return(EVAL$value)
}

History = function(index, points) {
  N = max(1, nrow(points))
  HIST = .C("R_history", index=as.integer(index), point = as.double(points), value = as.double(rep(1e100, N)), data_length=length(points), status = as.integer(0))
  if (HIST$status < N)
    warning("Not all of requested points were calculated correctly.")
  return(HIST$value)
}

# This doesn't really logout - it only unload DLL
Logout = function() {
  dyn.unload("RProxy.so")
}
