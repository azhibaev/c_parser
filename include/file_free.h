if (p->f)
{
	fclose(p->f);
	p->f = 0;
	p->flags = 0;
}

