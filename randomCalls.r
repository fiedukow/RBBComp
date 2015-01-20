dyn.load("RProxy.so", local=FALSE)
s=17
no_tracks = -1
x="012345678901234567890"
.C("R_init", status=as.integer(s))
.C("R_login", log = as.character("demoaccount"), pass = as.character("demopassword"), status = as.integer(s))
.C("R_numberOfTracks", noTracks = as.integer(no_tracks), status = as.integer(s))
.C("R_trackName", trackIndex=as.integer(0), name=as.character(""), status = as.integer(s))
.C("R_setTrack", name=as.character("trial"), status = as.integer(s))
.C("R_numberOfProblems", n = as.integer(17), status = as.integer(s))
.C("R_setProblem", n = as.integer(117), status = as.integer(s))
.C("R_dimension", n = as.integer(0), status = as.integer(s))
.C("R_budget", n = as.integer(0), status = as.integer(s))
.C("R_evaluations", n = as.integer(0), status = as.integer(s))
.C("R_evaluate", point = as.double(runif(4)), value = as.double(1e100), data_length=as.integer(4), status = as.integer(s))
.C("R_evaluate", point = as.double(runif(8)), value = as.double(c(1e100, 1e100)), data_length=as.integer(8), status = as.integer(s))
.C("R_history", index=as.integer(0), point = as.double(runif(8)), value = as.double(c(1e100, 1e100)), data_length=as.integer(8), status = as.integer(s))
dyn.unload("RProxy.so")

