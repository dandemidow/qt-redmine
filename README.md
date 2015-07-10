# qt-redmine
Qt client for the Redmine REST API

This library provide "users", "projects" and "issue" commands now.

/////////////////////////////////////////////////////////////////

Example

RedmineClient client(QUrl("http://my.redmine.org"), "user", "password", NULL);

client.reg<IssuePriorities> (&test, SLOT(onIssuePriority(QDomDocument)));
client.reg<UserCmd<Network::GET> > (&test, SLOT(onUsersReady(QDomDocument)));
client.reg<UserCmd<Network::POST> > (&test, SLOT(onUsersReady(QDomDocument)));
client.reg<ProjectCmd<Network::GET> > (&test, SLOT(onProjectsReady(QDomDocument)));
client.reg<IssueCmd<Network::GET> > (&test, SLOT(onIssuesReady(QDomDocument)));

client.run(IssueCmd<Network::GET>());

