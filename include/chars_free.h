if (p->buf)
{
	free(p->buf);
	p->buf = NULL;
	p->flags = 0;
}

