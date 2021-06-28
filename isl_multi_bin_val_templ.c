/*
 * Copyright 2013      Ecole Normale Superieure
 *
 * Use of this software is governed by the MIT license
 *
 * Written by Sven Verdoolaege,
 * Ecole Normale Superieure, 45 rue d'Ulm, 75230 Paris, France
 */

/* Apply "fn" to each of the elements of "multi" with as second argument "v".
 */
static __isl_give MULTI(BASE) *FN(MULTI(BASE),fn_val)(
	__isl_take MULTI(BASE) *multi,
	__isl_give EL *(*fn)(__isl_take EL *el, __isl_take isl_val *v),
	 __isl_take isl_val *v)
{
	int i;

	multi = FN(MULTI(BASE),cow)(multi);
	if (!multi || !v)
		goto error;

	for (i = 0; i < multi->n; ++i) {
		multi->u.p[i] = fn(multi->u.p[i], isl_val_copy(v));
		if (!multi->u.p[i])
			goto error;
	}

	isl_val_free(v);
	return multi;
error:
	isl_val_free(v);
	FN(MULTI(BASE),free)(multi);
	return NULL;
}
